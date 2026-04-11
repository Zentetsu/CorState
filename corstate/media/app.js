/*
 * File: app.js
 * Project: CorState
 * License: GPLv3
 */

const vscode = acquireVsCodeApi();

// ─── JointJS namespace ───────────────────────────────────────────────────────
const { dia, shapes, util } = joint;

// ─── Navigation stack ────────────────────────────────────────────────────────
// Each entry: { graph, label }
const navStack = [];
let currentGraph = null;
let paper = null;

// ─── Init canvas ─────────────────────────────────────────────────────────────
function initCanvas() {
    const container = document.getElementById('canvas-container');

    currentGraph = new dia.Graph({}, { cellNamespace: shapes });

    paper = new dia.Paper({
        el: container,
        model: currentGraph,
        width: container.clientWidth,
        height: container.clientHeight,
        gridSize: 15,
        drawGrid: { name: 'mesh', args: { color: '#3a3a3a' } },
        background: { color: '#1e1e1e' },
        cellViewNamespace: shapes,
        interactive: { linkMove: false },
    });

    // Resize paper when window resizes
    window.addEventListener('resize', () => {
        paper.setDimensions(container.clientWidth, container.clientHeight);
    });

    // Pan with middle mouse or right mouse
    let isPanning = false;
    let panStart = { x: 0, y: 0 };

    paper.on('blank:pointerdown', (evt, x, y) => {
        isPanning = true;
        panStart = { x: evt.clientX, y: evt.clientY };
    });

    paper.on('blank:pointermove', (evt) => {
        if (!isPanning) return;
        const dx = evt.clientX - panStart.x;
        const dy = evt.clientY - panStart.y;
        const t = paper.translate();
        paper.translate(t.tx + dx, t.ty + dy);
        panStart = { x: evt.clientX, y: evt.clientY };
    });

    paper.on('blank:pointerup', () => { isPanning = false; });

    // Zoom with mouse wheel
    container.addEventListener('wheel', (evt) => {
        evt.preventDefault();
        const delta = evt.deltaY > 0 ? 0.9 : 1.1;
        const scale = paper.scale();
        const newScale = Math.min(Math.max(scale.sx * delta, 0.2), 4);
        paper.scale(newScale, newScale);
    }, { passive: false });

    // Disable context menu on canvas
    container.addEventListener('contextmenu', (evt) => evt.preventDefault());

    // Drill-down on encapsulated state double-click
    paper.on('cell:pointerdblclick', (cellView) => {
        const model = cellView.model;
        if (model.prop('encapsulation') === true) {
            drillDown(model);
        }
    });

    // Transition mode: click source then target
    paper.on('cell:pointerclick', (cellView) => {
        if (!transitionMode) return;
        const model = cellView.model;
        if (model.isLink()) return;

        if (!transitionSource) {
            // First click — select source
            transitionSource = model;
            cellView.el.style.opacity = '0.6';
        } else {
            // Second click — create transition
            if (transitionSource.id !== model.id) {
                const label = `t${currentGraph.getLinks().length}`;
                const link = createTransition(transitionSource, model, label);
                currentGraph.addCell(link);
            }
            // Reset source highlight
            paper.findViewByModel(transitionSource).el.style.opacity = '1';
            exitTransitionMode();
        }
    });

    // Cancel transition mode on blank click
    paper.on('blank:pointerclick', () => {
        if (transitionMode && transitionSource) {
            paper.findViewByModel(transitionSource).el.style.opacity = '1';
            exitTransitionMode();
        }
    });

    updateBreadcrumb();
}

// ─── Navigation ──────────────────────────────────────────────────────────────
function drillDown(stateModel) {
    navStack.push({
        graph: currentGraph,
        label: stateModel.prop('stateName') || 'root'
    });

    const childData = stateModel.prop('childSM');
    currentGraph = new dia.Graph({}, { cellNamespace: shapes });

    if (childData) {
        loadSMIntoGraph(childData, currentGraph);
    }

    paper.setModel(currentGraph);
    updateBreadcrumb();
}

function navigateTo(index) {
    if (index >= navStack.length) return;
    const target = navStack[index];
    navStack.splice(index);
    currentGraph = target.graph;
    paper.setModel(currentGraph);
    updateBreadcrumb();
}

function updateBreadcrumb() {
    const el = document.getElementById('breadcrumb');
    const parts = ['root', ...navStack.map(e => e.label)];

    el.innerHTML = parts.map((label, i) => {
        if (i < parts.length - 1) {
            return `<span onclick="navigateTo(${i})">${label}</span> › `;
        }
        return `<strong>${label}</strong>`;
    }).join('');
}

// ─── State element ────────────────────────────────────────────────────────────
function createState(label, x, y, encapsulation = false) {
    const state = new shapes.standard.Rectangle({
        position: { x, y },
        size: { width: 120, height: 60 },
        attrs: {
            body: {
                fill: '#2d2d2d',
                stroke: encapsulation ? '#569cd6' : '#888',
                strokeWidth: encapsulation ? 2 : 1,
                rx: 5,
                ry: 5,
            },
            label: {
                text: label,
                fill: '#ccc',
                fontSize: 13,
            }
        }
    });

    state.prop('stateName', label);
    state.prop('encapsulation', encapsulation);
    state.prop('action', label);

    return state;
}

// ─── Start / End markers ──────────────────────────────────────────────────────
function createStartMarker(x, y) {
    const start = new shapes.standard.Circle({
        position: { x, y },
        size: { width: 24, height: 24 },
        attrs: {
            body: { fill: '#569cd6', stroke: 'none' },
            label: { text: '', }
        }
    });
    start.prop('markerType', 'start');
    return start;
}

function createEndMarker(x, y) {
    const end = new shapes.standard.Circle({
        position: { x, y },
        size: { width: 24, height: 24 },
        attrs: {
            body: { fill: '#1e1e1e', stroke: '#569cd6', strokeWidth: 3 },
            label: { text: '' }
        }
    });
    end.prop('markerType', 'end');
    return end;
}

// ─── Transition link ──────────────────────────────────────────────────────────
function createTransition(source, target, label) {
    const link = new shapes.standard.Link({
        source: { id: source.id },
        target: { id: target.id },
        attrs: {
            line: { stroke: '#888', strokeWidth: 1.5 },
        },
        labels: [{
            attrs: { text: { text: label, fill: '#ccc', fontSize: 11 } },
            position: 0.5
        }]
    });

    link.prop('evaluation', label);
    return link;
}

// ─── Load SM JSON into a graph ────────────────────────────────────────────────
function loadSMIntoGraph(sm, graph) {
    const stateMap = {};
    const states = sm.State || {};
    const transitions = sm.Transition || {};

    // Create start/end markers
    const startMarker = createStartMarker(60, 60);
    const endMarker = createEndMarker(600, 60);
    graph.addCells([startMarker, endMarker]);
    stateMap['inf_in'] = startMarker;
    stateMap['inf_out'] = endMarker;

    // Create states
    let x = 200, y = 150;
    Object.entries(states).forEach(([name, data], i) => {
        const state = createState(name, x + i * 160, y, data.encapsulation);
        state.prop('stateId', data.id);
        state.prop('action', data.action);
        if (data.encapsulation && data.childSM) {
            state.prop('childSM', data.childSM);
        }
        graph.addCell(state);
        stateMap[data.id] = state;
    });

    // Create transitions
    Object.entries(transitions).forEach(([name, data]) => {
        const srcKey = data.id_in === 'inf' ? 'inf_in' : data.id_in;
        const tgtKey = data.id_out === 'inf' ? 'inf_out' : data.id_out;

        const src = stateMap[srcKey];
        const tgt = stateMap[tgtKey];

        if (src && tgt) {
            const link = createTransition(src, tgt, data.evaluation);
            link.prop('transitionId', data.id);
            graph.addCell(link);
        }
    });
}

// ─── Export graph to SM JSON ──────────────────────────────────────────────────
function exportSM(graph) {
    const sm = { Variable: {}, State: {}, Transition: {} };
    let tId = 0;

    graph.getCells().forEach(cell => {
        if (cell.isLink()) {
            const src = graph.getCell(cell.get('source').id);
            const tgt = graph.getCell(cell.get('target').id);

            const id_in = src?.prop('markerType') === 'start' ? 'inf' : src?.prop('stateId');
            const id_out = tgt?.prop('markerType') === 'end' ? 'inf' : tgt?.prop('stateId');
            const label = cell.prop('evaluation') || `t${tId}`;

            const t = { id: tId++, id_in, id_out, evaluation: label };

            if (id_in === 'inf') sm.Transition['in'] = t;
            else if (id_out === 'inf') sm.Transition['out'] = t;
            else sm.Transition[label] = t;

        } else {
            const marker = cell.prop('markerType');
            if (marker) return;

            const name = cell.prop('stateName');
            const enc = cell.prop('encapsulation') || false;
            sm.State[name] = {
                id: cell.prop('stateId') ?? cell.id,
                action: cell.prop('action') || name,
                encapsulation: enc
            };
        }
    });

    return sm;
}

// ─── Transition drawing state ─────────────────────────────────────────────────
let transitionMode = false;
let transitionSource = null;

function enterTransitionMode() {
    transitionMode = true;
    transitionSource = null;
    document.getElementById('btn-add-transition').textContent = 'Cancel Transition';
    document.getElementById('canvas-container').style.cursor = 'crosshair';
}

function exitTransitionMode() {
    transitionMode = false;
    transitionSource = null;
    document.getElementById('btn-add-transition').textContent = 'Add Transition';
    document.getElementById('canvas-container').style.cursor = 'default';
}

// ─── Toolbar actions ──────────────────────────────────────────────────────────
document.getElementById('btn-add-state').addEventListener('click', () => {
    const t = paper.translate();
    const s = paper.scale();
    const name = `s${currentGraph.getCells().filter(c => !c.isLink() && !c.prop('markerType')).length}`;
    const state = createState(name, (200 - t.tx) / s.sx, (200 - t.ty) / s.sy);
    currentGraph.addCell(state);
});

document.getElementById('btn-add-transition').addEventListener('click', () => {
    if (transitionMode) {
        exitTransitionMode();
    } else {
        enterTransitionMode();
    }
});

document.getElementById('btn-save').addEventListener('click', () => {
    const sm = exportSM(currentGraph);
    vscode.postMessage({ command: 'save', data: { SM: { StateMachine: sm } } });
});

// ─── VSCode message handler ───────────────────────────────────────────────────
window.addEventListener('message', (event) => {
    const { command, data } = event.data;

    if (command === 'new') {
        currentGraph.clear();
        const start = createStartMarker(60, 200);
        const end = createEndMarker(600, 200);
        currentGraph.addCells([start, end]);

    } else if (command === 'load') {
        currentGraph.clear();
        const sm = data?.SM?.StateMachine;
        if (sm) loadSMIntoGraph(sm, currentGraph);
    }
});

// ─── Boot ─────────────────────────────────────────────────────────────────────
initCanvas();
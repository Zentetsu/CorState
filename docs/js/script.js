/*
 * File: script.js
 * Created Date: Friday, September 5th 2020, 9:52:35 pm
 * Author: Zentetsu
 *
 * ----
 *
 * Last Modified:
 * Modified By:
 *
 * ----
 *
 * Project: CorState
 * Copyright (c) 2020 Zentetsu
 *
 * ----
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * ----
 *
 * HISTORY:
 * 2020-09-21	Zen	Adding editable name for state and transition
 */


// Init GRID
var canvas = new fabric.Canvas('canvas', { selection: false });
var canvasWidth =  window.innerWidth * 0.98;
var canvasHeight = window.innerHeight * 0.95;
var unitScale = 10;
var grid = 15;

fabric.Object.prototype.originX = fabric.Object.prototype.originY = 'center';

canvas.setWidth(canvasWidth);
canvas.setHeight(canvasHeight);

// Create GRID
for (var i = 0; i < (canvasWidth / grid); i++) {
    canvas.add(new fabric.Line([ i * grid, 0, i * grid, canvasHeight], { type:'line', stroke: '#ccc', selectable: false }));
    canvas.add(new fabric.Line([ 0, i * grid, canvasWidth, i * grid], { type: 'line', stroke: '#ccc', selectable: false }))
}

function calcArrowAngle(x1, y1, x2, y2) {
    var angle = 0,
        x, y;

    x = (x2 - x1);
    y = (y2 - y1);

    if(x === 0) {
        angle = (y === 0) ? 0 : (y > 0) ? Math.PI / 2 : Math.PI * 3 / 2;
    } else if (y === 0) {
        angle = (x > 0) ? 0 : Math.PI;
    } else {
        angle = (x < 0) ? Math.atan(y / x) + Math.PI : (y < 0) ? Math.atan(y / x) + (2 * Math.PI) : Math.atan(y / x);
    }

    return (angle * 180 / Math.PI);
}

// Snap moved State or Transition to the GRID
canvas.on('object:moving', function(options) {
    if(options.target.type === 'state') {
        options.target.set({
            left: Math.round(options.target.left / grid) * grid,
            top: Math.round(options.target.top / grid) * grid
        });
    } else {
        var p = options.target;

        options.target.set({
            left: Math.round(options.target.left / grid) * grid,
            top: Math.round(options.target.top / grid) * grid
        });

        if(options.target.part === 'in') {
            p.line && p.line.set({ 'x1': Math.round(p.left / grid) * grid, 'y1': Math.round(p.top / grid) * grid});
            aa = calcArrowAngle(p.line.get('x1'), p.line.get('y1'), p.line.get('x2'), p.line.get('y2'));

            p.line.arrow.set({
                angle: aa +90
            });

            if(p.line.get('y1') === p.line.get('y2')) {
                add_top = -10;
                add_left = 0;
            } else if(p.line.get('x1') === p.line.get('x2')) {
                add_top = 0;
                add_left = 30;
            }

            p.line.text.set({
                left: (p.line.get('x1') + p.line.get('x2')) / 2 + add_left,
                top: (p.line.get('y1') + p.line.get('y2')) / 2 + add_top
            });
        } else if(options.target.part === 'out') {
            p.line && p.line.set({ 'x2': Math.round(p.left / grid) * grid, 'y2': Math.round(p.top / grid) * grid});
            aa = calcArrowAngle(p.line.get('x1'), p.line.get('y1'), p.line.get('x2'), p.line.get('y2'));

            options.target.set({
                angle: aa +90
            });

            if(p.line.get('y1') === p.line.get('y2')) {
                add_top = 10;
                add_left = 0;
            } else if(p.line.get('x1') === p.line.get('x2')) {
                add_top = 0;
                add_left = 30;
            }

            p.line.text.set({
                left: (p.line.get('x1') + p.line.get('x2')) / 2 + add_left,
                top: (p.line.get('y1') + p.line.get('y2')) / 2 + add_top
            });
        }
        // else if(options.target.part === "segment") {
        //     p.circle && p.circle.set({ 'left': Math.round(p.left / grid) * grid, 'top': Math.round(p.top / grid) * grid - p.height / 2});
        //     p.arrow && p.arrow.set({ 'left': Math.round(p.left / grid) * grid, 'top': Math.round(p.top / grid) * grid + p.height / 2});
        // }
    }
});

canvas.on('object:modified', function(options) {
    var newWidth = (Math.round(options.target.width * options.target.scaleX / grid)) * grid;
    var newHeight = (Math.round(options.target.height  * options.target.scaleY / grid)) * grid;

    options.target.set({
        width: newWidth,
        height: newHeight,
        scaleX: 1,
        scaleY: 1
    });
});

canvas.on('selection:created', function(options) {
    console.log(options.target.type)
    if(options.target.part === "text") {
        document.getElementById("rename").value = options.target.text;
    } else {
        document.getElementById("rename").value = options.target.text.text;
    }
});

canvas.on('selection:updated', function(options) {
    console.log(options.target.type)
    if(options.target.part === "text") {
        document.getElementById("rename").value = options.target.text;
    } else {
        document.getElementById("rename").value = options.target.text.text;
    }
});

canvas.on('selection:cleared', function(options) {
    document.getElementById("rename").value = "";
});

// Adding State to the GRID
function addState() {
    //TODO add ID
    id = 0;

    var state = new fabric.Rect({
        left: 60,
        top: 60,
        width: 90,
        height: 90,
        type: 'state',
        part: 'state',
        fill: '',
        stroke:'Black',
        originX: 'left',
        originY: 'top',
        rx: 5,
        ry: 5,
        id: id,
        hasControls: true,
        hasRotatingPoint: false,
        lockRotation: true
    });

    var text = new fabric.Text('function', {
        left: 105,
        top: 105,
        type: 'state',
        part: 'text',
        fontSize: 15,
        originX: 'center',
        originY: 'center',
        selectable: false,
        hasBorders: false,
        hasControls: false,
        lockScalingX: true,
        lockScalingY: true,
        lockRotation: true,
      });

    var group = new fabric.Group([ state, text ], {
        type: 'state'
    });

    group.text = text;

    canvas.add(group);
}

// Adding a Transition to the GRID
function addTransition() {
    //TODO add ID
    id = 0;
    console.log("here");

    var circle = new fabric.Circle({
        left: 60,
        top: 60,
        fill: '#fff',
        stroke: '#666',
        strokeWidth: 4,
        radius: 4,
        hasBorders: false,
        hasControls: false,
        type: 'transition',
        part: 'in'
    });

    var line = new fabric.Line([ 60, 60, 60, 120 ], {
        type: 'line',
        originX: 'center',
        originY: 'center',
        fill: '',
        stroke: '#666',
        strokeWidth: 2,
        selectable: true,
        hasBorders: false,
        hasControls: false,
        hasBorders: false,
        hasControls: false,
        lockScalingX: true,
        lockScalingY: true,
        lockRotation: true,
        lockMovementX: true,
        lockMovementY: true,
        type: 'transition',
        part: 'segment'
    });

    var text = new fabric.Text('function', {
        left: (line.get('x1') + line.get('x2')) / 2 + 30,
        top: (line.get('y1') + line.get('y2')) / 2,
        fontSize: 15,
        originX: 'center',
        originY: 'center',
        selectable: true,
        hasBorders: false,
        hasControls: false,
        lockScalingX: true,
        lockScalingY: true,
        lockRotation: true,
        lockMovementX: true,
        lockMovementY: true,
        type: 'transition',
        part: 'text',
      });

    var centerX = (line.x1 + line.x2) / 2,
        centerY = (line.y1 + line.y2) / 2,
        deltaX = line.left - centerX,
        deltaY = line.top - centerY;

    arrow = new fabric.Triangle({
        left: line.get('x2') + deltaX,
        top: line.get('y2') + deltaY,
        originX: 'center',
        originY: 'center',
        // pointType: 'arrow_start',
        angle: 180,
        width: 15,
        height: 15,
        fill: '#666',
        hasBorders: false,
        hasControls: false,
        lockScalingX: true,
        lockScalingY: true,
        lockRotation: true,
        type: 'transition',
        part: 'out'
    });

    line.circle = circle;
    line.arrow = arrow;
    line.text = text;

    circle.line = line;
    circle.arrow= arrow;
    circle.text = text;

    arrow.line = line;
    arrow.circle = circle;
    arrow.text = text;

    text.line = line;

    canvas.add(line, circle, arrow, text);
}

function deleteList(listItems) {
    if(listItems !== undefined) {
        var len = listItems.length;
        var list = []

        for(var i = 0; i < len; i+= 1) {
            var item = listItems[i];
            if(item.type === "state" || item.type === "transition") {
                list.push(item);
            }
        }

        len = list.length;

        for(var i = 0; i < len; i+= 1) {
            canvas.remove(list[i]);
        }
    }
}

// Method to delete all states and transitions
function deleteAllObjects() {
    var objects = canvas.getObjects();
    deleteList(objects);
}

// Actions
var addingState = document.getElementById('addnewstate');
addingState.addEventListener('click', addState);

var addingTransition = document.getElementById('addnewtransition');
addingTransition.addEventListener('click', addTransition);

var deletingObjects = document.getElementById('delete');
deletingObjects.addEventListener('click', deleteAllObjects);

document.addEventListener('keydown', function(event) {
    var keyPressed = event.keyCode;
    if(keyPressed == 46) {
        var activeObject = canvas.getActiveObject();
        if(activeObject !== null && activeObject.type === "state") {
            canvas.remove(activeObject);
        } else if(activeObject !== null && activeObject.type === "transition") {
            if(activeObject.part === "in") {
                canvas.remove(activeObject.text);
                canvas.remove(activeObject.line);
                canvas.remove(activeObject.arrow);
                canvas.remove(activeObject);
            } else if(activeObject.part === "out") {
                canvas.remove(activeObject.text);
                canvas.remove(activeObject.line);
                canvas.remove(activeObject.circle);
                canvas.remove(activeObject);
            } else {
                canvas.remove(activeObject.text);
                canvas.remove(activeObject.arrow);
                canvas.remove(activeObject.circle);
                canvas.remove(activeObject);
            }
        }
    } else if(keyPressed === 13) {
        var activeObject = canvas.getActiveObject();
        if(activeObject !== null && document.getElementById("rename").value !== "") {
            if(activeObject.part === "text") {
                activeObject.set('text', document.getElementById("rename").value);
            } else {
                activeObject.text.set('text', document.getElementById("rename").value);
            }
            document.getElementById("rename").value = "";
            canvas.renderAll();
        }
    }
});
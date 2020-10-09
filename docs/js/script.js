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
 * 2020-10-09	Zen	Name update correction
 * 2020-10-08	Zen	Adding dynamic update transition encapsulation
 * 2020-10-08	Zen	Adding dynamic update state encapsulation
 * 2020-10-01	Zen	Adding state encapsulation detection
 * 2020-09-30	Zen	Refactoring
 * 2020-09-26	Zen	Adding download and upload option
 * 2020-09-24	Zen	Updating wavepoints creation and deletion
 * 2020-09-23	Zen	State name position correction
 * 2020-09-23	Zen	Removing wavepoint
 * 2020-09-22	Zen	Adding wavepoint
 * 2020-09-21	Zen	Adding editable name for state and transition
 */


// Init GRID
var canvas = new fabric.Canvas('canvas', { selection: false, preserveObjectStacking: true });
var canvasWidth =  document.getElementById("content").clientWidth;
var canvasHeight = document.getElementById("content").clientHeight;
var unitScale = 10;
var grid = 15;
var ID_transition = 0;
var ID_state = 0;

fabric.Object.prototype.originX = fabric.Object.prototype.originY = 'center';
fabric.Object.prototype.transparentCorners = false;

canvas.setWidth(canvasWidth);
canvas.setHeight(canvasHeight);

document.getElementById("rename").readOnly = true;

// Create GRID
initGrid(canvas, canvasWidth, canvasHeight, grid);

// Snap moved State or Transition to the GRID
canvas.on('object:moving', function(options) {
    if(options.target.n_type === 'state') {
        options.target.set({
            left: Math.round(options.target.left / grid) * grid,
            top: Math.round(options.target.top / grid) * grid
        });

        moveText(options.target.id, options.target.n_type, options.target.left+30, options.target.top+10);

        updateSM();

        if(options.target.encapsuler === NaN) {
            canvas.moveTo(options.target, 0);
            options.target.moveTo(0);
            options.target.index = 0;
        } else {
            var index = getIndex(options.target.encapsuler)+1;
            canvas.moveTo(options.target, index);
            options.target.moveTo(index);
            options.target.index = index;
        }

    } else {
        var p = options.target;

        p.set({
            left: Math.round(p.left / grid) * grid,
            top: Math.round(p.top / grid) * grid
        });

        if(p.part === 'in' || p.part === 'c') {
            moveLine(p.line, Math.round(p.left / grid) * grid, Math.round(p.top / grid) * grid, null, null);
            var line_pos = getLine(p.line);
            moveLine(p.line2, null, null, Math.round(p.left / grid) * grid, Math.round(p.top / grid) * grid);

            aa = calcArrowAngle(line_pos[0], line_pos[1], line_pos[2], line_pos[3]);
            moveArrow(p.arrow, aa + 90);

            var add_top = 0;
            var add_left = 0;

            if(line_pos[1] === line_pos[3]) {
                add_top = -10;
                add_left = 0;
            } else if(line_pos[0] ===line_pos[2]) {
                add_top = 0;
                add_left = 30;
            }
        } else if(p.part === 'out') {
            moveLine(p.line, null, null, Math.round(p.left / grid) * grid, Math.round(p.top / grid) * grid);
            var line_pos = getLine(p.line);
            aa = calcArrowAngle(line_pos[0], line_pos[1], line_pos[2], line_pos[3]);
            moveArrow(p.id, aa + 90);

            var add_top = 0;
            var add_left = 0;

            if(line_pos[1] === line_pos[3]) {
                add_top = 10;
                add_left = 0;
            } else if(line_pos[0] ===line_pos[2])  {
                add_top = 0;
                add_left = 30;
            }
        }

        var n_left = (line_pos[0] + line_pos[2]) / 2 + add_left;
        var n_top = (line_pos[1] + line_pos[3]) / 2 + add_top;

        moveText(p.id, p.n_type, n_left, n_top);

        updateSM();
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

    if(options.target.n_type === "state") {
        moveText(options.target.id, options.target.n_type, options.target.left + 30, options.target.top + 10);
    }
});

canvas.on('selection:created', function(options) {
    var txt = getText(options.target.text, options.target.n_type);
    document.getElementById("rename").value = txt.text;
});

canvas.on('selection:updated', function(options) {
    var txt = getText(options.target.text, options.target.n_type);
    document.getElementById("rename").value = txt.text;
});

canvas.on('selection:cleared', function(options) {
    document.getElementById("rename").value = "";
    document.getElementById("rename").readOnly = true;
});

// Actions
var addingState = document.getElementById('addnewstate');
addingState.addEventListener('click', addState);

var addingTransition = document.getElementById('addnewtransition');
addingTransition.addEventListener('click', addTransition);

var deletingObjects = document.getElementById('delete');
deletingObjects.addEventListener('click', deleteAllObjects);

var downloadFile = document.getElementById('download');
downloadFile.addEventListener('click', downloadingFile)

var uploadFile = document.getElementById('file-selector');
uploadFile.addEventListener('change', uploadingFile);

document.addEventListener('keydown', function(event) {
    var keyPressed = event.keyCode;
    if(keyPressed == 46) {
        var activeObject = canvas.getActiveObject();
        if(activeObject !== null && activeObject.n_type === "state") {
            deleteID(activeObject.id, "state");
        } else if(activeObject !== null && activeObject.n_type === "transition") {
            deleteID(activeObject.id, "transition");
        }
    } else if(keyPressed === 13) {
        var activeObject = canvas.getActiveObject();

        if(activeObject !== null && document.getElementById("rename").value !== "") {
            updateText(activeObject.id, activeObject.n_type, document.getElementById("rename").value);

            document.getElementById("rename").readOnly = true;
            document.getElementById("rename").blur();

            canvas.renderAll();
        }
    } else if(keyPressed === 82 && document.querySelector('input:focus') === null) {
        var activeObject = canvas.getActiveObject();

        if(activeObject !== undefined && activeObject !== null) {
            sleep(100).then(() => {
                document.getElementById("rename").readOnly = false;
                document.getElementById("rename").focus();
                document.getElementById("rename").select();
            })
        }
    } else if(keyPressed === 83 && document.querySelector('input:focus') === null) {
        var activeObject = canvas.getActiveObject();
        if(activeObject !== undefined && activeObject !== null && activeObject.n_type === "transition") {
            var object = activeObject;

            if(activeObject.part === "in") {
                object = getArrow(activeObject.f_arrow);
            }

            var val_l = getLine(object.line);

            var n_circle = new fabric.Circle({
                type: 'circle',
                left: val_l[4],
                top: val_l[5],
                fill: '#666',
                radius: 4,
                hasBorders: false,
                hasControls: false,
                n_type: 'transition',
                part: 'c'
            });

            var n_line = new fabric.Line([n_circle.left, n_circle.top, val_l[2], val_l[3]], {
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
                n_type: 'transition',
                part: 'segment'
            });

            if(object.part === "out") {
                n_line.id = object.line + 0.01;
                n_circle.id = object.circle + 0.01;

                n_line.arrow = object.id;
                n_circle.arrow = object.id;

                n_line.circle = n_circle.id;
                n_circle.circle = object.circle;

                n_line.text = object.text;
                n_circle.text = object.text;

                n_circle.line2 = object.line;
                n_circle.line = n_line.id;


                circle = getCircle(object.circle);
                circle.arrow = n_circle.id;

                line = getLine2(object.line);
                line.arrow = n_circle.id;
                moveLine(object.line, null, null, n_circle.left, n_circle.top);

                object.line = n_line.id;
                object.circle = n_circle.id;

                canvas.add(n_line, n_circle);
            }

            canvas.renderAll();
        }
    } else if(keyPressed === 68 && document.querySelector('input:focus') === null) {
        var activeObject = canvas.getActiveObject();
        if(activeObject !== undefined && activeObject !== null && activeObject.n_type === "transition") {
            var object = activeObject;

            if(activeObject.part === "in") {
                object = getArrow(activeObject.f_arrow);
            }

            var del_circle = getCircle(object.circle)

            if(object.part === "out" && del_circle.part === "c") {
                var del_line = getLine2(del_circle.line);
                var circle = getCircle(del_circle.circle);

                circle.arrow = object.id;

                object.circle = circle.id;
                object.line = circle.line;

                moveLine(object.line, null, null, object.left, object.top);

                canvas.remove(del_circle);
                canvas.remove(del_line);
            }

            canvas.renderAll();
        }
    }
});
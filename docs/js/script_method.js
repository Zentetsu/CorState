/*
 * File: script_method.js
 * Created Date: Sunday, September 0th 2020, 11:33:14 am
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
 * 2020-10-08	Zen	Adding dynamic update state encapsulation
 * 2020-10-01	Zen	Adding state encapsulation detection
 * 2020-09-30	Zen	Refactoring
 */


const sleep = (milliseconds) => {
    return new Promise(resolve => setTimeout(resolve, milliseconds))
}

function initGrid() {
    for (var i = 0; i < (canvasWidth / grid); i++) {
        var color;
        if(i === 0 || i % 4 === 0) {
            color = '#BFBFBF';
        } else {
            color = '#D9D9D9'
        }

        canvas.add(new fabric.Line([ i * grid, 0, i * grid, canvasHeight], { type: 'line', stroke: color, selectable: false }));
        canvas.add(new fabric.Line([ 0, i * grid, canvasWidth, i * grid], { type: 'line', stroke: color, selectable: false }))
    }
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

function updateSM() {
    var l_s = [];

    canvas.forEachObject(function(obj) {
        if(obj.n_type === "state" && obj.part === "state") {
            console.log(obj.id, getContainer(obj));
            obj.encapsuler = getContainer(obj);
        }
    });
}

function getContainer(object) {
    object.setCoords();

    var list = [];

    canvas.forEachObject(function(obj) {
        if(object.isContainedWithinObject(obj) && obj.n_type === "state" && obj.part === "state") {
            if(object.id !== obj.id) {
                list.push(obj);
            }
        }
    });

    if(list.length === 0) {
        return NaN;
    } else if(list.length === 1) {
        return list[0].id;
    }

    var find = false;
    var cur = 0;

    while(!find) {
        var s = list[cur];

        for(let i = 0; i < list.length; i++) {
            if(s === undefined) {
                return NaN;
            }
            if(s.id !== list[i].id) {
                if(!s.isContainedWithinObject(list[i])) {
                    find = false;
                    break;
                } else {
                    find = true;
                }
            }
        }

        if(find) {
            break;
        } else {
            cur += 1;
        }
    }

    return list[cur].id;
}

function checkEncapsuled(object) {
    object.setCoords();

    var list = [];

    canvas.forEachObject(function(obj) {
        if(object.isContainedWithinObject(obj) && !getIntersection(object) && obj.n_type === "state") {
            if(object.n_type === "state" && obj.id !== object.id || object.n_type === "transition") {
                list.push(obj);
                console.log("toto");
            }
        }
    });

    if (list.length === 1) {
        if(object.encapsuled !== list[0].id) {
            setEncapsuler(object.encapsuled, object.id, false, object.n_type);
        }
        setEncapsuler(list[0].id, object.id, true, object.n_type);
        setEncapsuled(object.id, list[0].id);
    } else if(list.length > 1) {
        var size = list.length;
        var cur = 0;
        while(size > 1) {
            var to_pop = list[cur];
            var popping = false;

            for (let i = 0; i < list.length; i++) {
                if(to_pop.isContainedWithinObject(list[i])) {
                    popping = true;
                }
            }

            if(popping) {
                list.shift();
                size = list.length;
                cur = 0;
            } else {
                cur += 1;
            }
        }

        setEncapsuler(list[0].id, object.id, true, object.n_type);
        setEncapsuled(object.id, list[0].id);
    } else {
        setEncapsuler(object.encapsuled, object.id, false, object.n_type);
        setEncapsuled(object.id, NaN);
    }
}

function checkEncapsuler(object) {
    object.setCoords();

    var list = [];

    canvas.forEachObject(function(obj) {
        if(obj.isContainedWithinObject(object) && obj.id !== object.id) {
            if(isNaN(obj.encapsuled) || obj.encapsuled === object.encapsuled) {
                list.push(obj);
                object.encapsuler.push(obj.id);
                console.log("toto");
            }
        }
    });

    if(list.length >= 1) {
        var cur = 0;
        var size = object.encapsuler.length;

        while(size > list.length) {
            var pres = false;

            for(let i = 0; i < list.length; i++) {
                if(list[i].id === object.encapsuler[cur]) {
                    pres = true;
                }
            }

            if(!pres) {
                var state = getState(object.encapsuler[cur]);
                state.set({encapsuled: object.encapsuled});

                object.encapsuled.splice(cur, 1);
                size = object.encapsuled.length;
            } else {
                cur += 1;
            }
        }

    }
}

function getIntersection(object) {
    var inter = false;
    object.setCoords();
    canvas.forEachObject(function(obj) {
        if(object.n_type === "transition" && obj.type !== "line" && obj.n_type !== "transition") {
            if(object.intersectsWithObject(obj) && !object.isContainedWithinObject(obj)) {
                inter = true;
            }
        }
    });

    return inter;
}

function setEncapsuler(id, id_e, add, type) {
    canvas.forEachObject(function(obj) {
        if(obj.n_type === "state" && obj.part === "state" && obj.id === id && type === "state") {
            if(add) {
                if(!obj.encapsuler.includes(id_e)) {
                    obj.encapsuler.push(id_e);
                }
            } else {
                for(let i = 0; i < obj.encapsuler.length; i++) {
                    if(obj.encapsuler[i] === id_e) {
                        obj.encapsuler.splice(i, 1);
                    }
                }
            }
        } else if(obj.n_type === "state" && obj.part === "state" && obj.id === id && type === "transition") {
            if(add) {
                if(!obj.encapsuler_a.includes(id_e)) {
                    obj.encapsuler_a.push(id_e);
                }
            } else {
                for(let i = 0; i < obj.encapsuler_a.length; i++) {
                    if(obj.encapsuler_a[i] === id_e) {
                        obj.encapsuler_a.splice(i, 1);
                    }
                }
            }
        }
    });
}

function setEncapsuled(id, id_e) {
    canvas.forEachObject(function(obj) {
        if((obj.n_type === "state" && obj.part === "state" || obj.n_type == "transition" && (obj.part === "in" || obj.part === "out")) && obj.id === id) {
            if(obj.part === "out") {
                obj.set({encapsuled: -id_e});
            } else {
                obj.set({encapsuled: id_e});
            }
        }
    });
}

function getIndex(id) {
    var index = -1;
    canvas.forEachObject(function(obj) {
        if(obj.n_type === "state" && obj.part === "state" && obj.id === id) {
            index = obj.get('index');
        }
    });

    return index;
}

function addState() {
    var state = new fabric.Rect({
        type: 'rect',
        left: 60,
        top: 60,
        width: 90,
        height: 90,
        n_type: 'state',
        part: 'state',
        fill: '',
        stroke:'#666',
        strokeWidth: 2,
        originX: 'left',
        originY: 'top',
        rx: 5,
        ry: 5,
        id: ID_state,
        hasControls: true,
        hasRotatingPoint: false,
        lockRotation: true,
        encapsuler: NaN,
        index: 0,
    });

    var text = new fabric.Text('function', {
        type: 'text',
        left: (state.left) + 30,
        top: (state.top) + 10,
        n_type: 'state',
        part: 'text',
        fontSize: 15,
        originX: 'center',
        originY: 'center',
        id: ID_state,
        selectable: false,
        hasBorders: false,
        hasControls: false,
        lockScalingX: true,
        lockScalingY: true,
        lockRotation: true,
      });

    state.text = text.id;

    canvas.add(text, state);

    ID_state++;
}

function addTransition() {
    var circle = new fabric.Circle({
        type: 'circle',
        left: 60,
        top: 60,
        fill: '#fff',
        stroke: '#666',
        strokeWidth: 4,
        radius: 4,
        id: ID_transition,
        hasBorders: false,
        hasControls: false,
        n_type: 'transition',
        part: 'in',
        id_state: null,
        encapsuled: NaN,
        index: 0,
    });

    var line = new fabric.Line([ 60, 60, 60, 120 ], {
        type: 'line',
        originX: 'center',
        originY: 'center',
        fill: '',
        stroke: '#666',
        strokeWidth: 2,
        id: ID_transition,
        selectable: false,
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
        part: 'segment',
        next: null
    });

    var text = new fabric.Text('function', {
        type: 'text',
        left: (line.get('x1') + line.get('x2')) / 2 + 30,
        top: (line.get('y1') + line.get('y2')) / 2,
        fontSize: 15,
        originX: 'center',
        originY: 'center',
        id: ID_transition,
        selectable: false,
        hasBorders: false,
        hasControls: false,
        lockScalingX: true,
        lockScalingY: true,
        lockRotation: true,
        lockMovementX: true,
        lockMovementY: true,
        n_type: 'transition',
        part: 'text',
      });

    var centerX = (line.x1 + line.x2) / 2,
        centerY = (line.y1 + line.y2) / 2,
        deltaX = line.left - centerX,
        deltaY = line.top - centerY;

    arrow = new fabric.Triangle({
        type: 'triangle',
        left: line.get('x2') + deltaX,
        top: line.get('y2') + deltaY,
        originX: 'center',
        originY: 'center',
        angle: 180,
        width: 15,
        height: 15,
        fill: '#666',
        id: ID_transition,
        hasBorders: false,
        hasControls: false,
        lockScalingX: true,
        lockScalingY: true,
        lockRotation: true,
        n_type: 'transition',
        part: 'out',
        id_state: null,
        encapsuled: NaN,
        index: 0,
    });

    line.circle = circle.id;
    line.arrow = arrow.id;
    line.text = text.id;

    circle.line = line.id;
    circle.line2 = null;
    circle.arrow = arrow.id;
    circle.text = text.id;
    circle.f_arrow = arrow.id;

    arrow.line = line.id;
    arrow.circle = circle.id;
    arrow.f_circle = circle.id;
    arrow.text = text.id;

    text.line = line.id;

    canvas.add(line, circle, arrow, text);

    ID_transition++;
}

function updateText(id, type, new_text) {
    canvas.forEachObject(function(obj) {
        if(obj.n_type === type && obj.part === "text" && obj.id === id) {
            obj.set('text', new_text);
        }
    });
}

function moveText(id, type, left, top) {
    canvas.forEachObject(function(obj) {
        if(obj.n_type === type && obj.part === "text" && obj.id === id) {
            obj.set({left: left, top: top});
        }
    });
}

function getText(id) {
    var val;

    canvas.forEachObject(function(obj) {
        if(obj.part === "text" && obj.id === id) {
            // console.log("toto")
            val = obj;
        }
    });

    return val;
}

function getState(id) {
    var val;

    canvas.forEachObject(function(obj) {
        if(obj.part === "state" && obj.part ==="state" && obj.id === id) {
            // console.log("toto")
            val = obj;
        }
    });

    return val;
}

function moveLine(id, x1, y1, x2, y2) {
    if(id !== null) {
        canvas.forEachObject(function(obj) {
            if(obj.part === "segment" && obj.id === id) {
                if(x2 === null && y2 === null) {
                    obj.set({'x1': x1, 'y1': y1});
                } else {
                    obj.set({'x2': x2, 'y2': y2});
                }
            }
        });
    }
}

function getLine(id) {
    var val;

    canvas.forEachObject(function(obj) {
        if(obj.part === "segment" && obj.id === id) {
            val = [obj.get('x1'), obj.get('y1'), obj.get('x2'), obj.get('y2'), obj.get('left'), obj.get('top')];
        }
    });

    return val;
}

function moveArrow(id, angle) {
    canvas.forEachObject(function(obj) {
        if(obj.part === "out" && obj.id === id) {
            obj.set({angle: angle});
        }
    });
}

function getArrow(id) {
    var arrow;

    canvas.forEachObject(function(obj) {
        if((obj.part === "out" || obj.part === "c") && obj.id === id) {
            arrow = obj;
        }
    });

    return arrow;
}

function getCircle(id) {
    var circle;

    canvas.forEachObject(function(obj) {
        if((obj.part === "in" || obj.part === "c")  && obj.id === id) {
            circle = obj;
        }
    });

    return circle;
}

function getLine2(id) {
    var line;

    canvas.forEachObject(function(obj) {
        if(obj.part === "segment" && obj.id === id) {
            line = obj;
        }
    });

    return line;
}

function setCircleArrow(id, arrow_id) {
    canvas.forEachObject(function(obj) {
        if((obj.part === "in" || obj.part === "c") && obj.id === id) {
            obj.set({"arrow": arrow_id});
        }
    });
}

function setLineArrow(id, arrow_id) {
    canvas.forEachObject(function(obj) {
        if(obj.part === "segment" && obj.id === id) {
            obj.set({"arrow": arrow_id});
        }
    });
}

function deleteList(listItems) {
    if(listItems !== undefined) {
        var len = listItems.length;
        var list = []

        for(var i = 0; i < len; i+= 1) {
            var item = listItems[i];
            if(item.n_type === "state" || item.n_type === "transition") {
                list.push(item);
            }
        }

        len = list.length;

        for(var i = 0; i < len; i+= 1) {
            canvas.remove(list[i]);
        }
    }
}

function deleteID(ID, type) {
    var listItems = canvas.getObjects();
    var len = listItems.length;
    var list = []

    for(var i = 0; i < len; i+= 1) {
        var item = listItems[i];

        if(item.n_type === type && Math.trunc(item.id) === ID) {
            list.push(item);
        }
    }

    len = list.length;

    for(var i = 0; i < len; i+= 1) {
        canvas.remove(list[i]);
    }
}

function deleteAllObjects() {
    var objects = canvas.getObjects();
    deleteList(objects);
}

function dumpSM() {
    var d = {"path": "", "StateMachine": {"Variable": {}, "State": {}, "Transition": {}}};

    canvas.forEachObject(function(obj) {
        if(obj.n_type === "state") {
            var s = {
                        "id":obj.id,
                        "action": obj.text,
                        "encapsulation": obj.encapsuler
                    }

            d["StateMachine"]["State"][obj.text] = s;
        } else if(obj.n_type === "transition" && obj.part === "circle") {

            var t = {
                        "id": obj.id,
                        "id_in": "inf",
                        "id_out": "inf",
                        "evaluation": obj.text
                    }

            canvas.forEachObject(function(obj2) {
                if(obj.intersectsWithObject(obj2) && obj2.n_type === "state") {
                    t["id_in"] = obj.id;
                }
            });

            canvas.forEachObject(function(obj2) {
                if(obj.f_arrow.intersectsWithObject(obj2) && obj2.n_type === "state") {
                    t["id_out"] = obj.id;
                }
            });

            if(t["id_in"] === "inf" && obj.encapsuled) {
                t["id_in"] = obj.encapsuler_id;
            } else if(t["id_out"] === "inf" && obj.encapsuled) {
                t["id_out"] = -obj.encapsuler_id;
            }

            if(t["id_in"] === "inf") {
                d["StateMachine"]["Transition"]["in"] = t;
            } else if(t["id_out"] === "inf") {
                d["StateMachine"]["Transition"]["out"] = t;
            } else {
                d["StateMachine"]["Transition"][obj.text] = t;
            }
        }
    });
}

function downloadingFile() {
    var text = JSON.stringify(canvas.toJSON(['selectable', 'hasBorders', 'hasControls', 'lockScalingX', 'lockScalingY',
                                             'lockRotation', 'lockMovementX', 'lockMovementY', 'id', 'text', 'n_type',
                                             'part', 'line', 'line2', 'circle', 'arrow', 'f_circle', 'f_arrow', 'encapsuler',
                                            'encapsuled', 'index']));

    // var dump = dumpSM();
    var file = "GFG.json";

    var element = document.createElement('a');
    element.setAttribute('href', 'data:text/plain;charset=utf-8, ' + encodeURIComponent(text));
    element.setAttribute('download', file);

    document.body.appendChild(element);

    element.click();

    document.body.removeChild(element);
}
function uploadingFile(event) {
    var reader = new FileReader();
    reader.onload = handleFileLoad;
    reader.readAsText(event.target.files[0]);
}

function handleFileLoad(event) {
  canvas.loadFromJSON(event.target.result);
}
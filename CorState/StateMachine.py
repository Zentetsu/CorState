'''
File: StateMachine.py
Created Date: Thursday, July 4th 2020, 10:01:03 pm
Author: Zentetsu

----

Last Modified:
Modified By:

----

Project: CorState
Copyright (c) 2020 Zentetsu

----

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

----

HISTORY:
2020-09-10	Zen	Refactoring the StateMachine structure
'''


import json
import os
from .State import State
from .Transition import Transition


class StateMachine:
    """StateMachine class
    """
    def __init__(self, name: str):
        """Class constructor
        """
        self._name = name
        self._states = {}
        self._transitions = {}

        self._data = None

    def start(self):
        """Method that launches the state StateMachine
        """
        self._checkStateMachineIntegrity()

        _stateID = -1
        _breaked = True

        while _breaked:
            _breaked = False

            for tr in self._transitions.keys():
                if self._transitions[tr].getInOutID()[0] == _stateID and _stateID and self._transitions[tr].evaluate():
                    _stateID = self._transitions[tr].getInOutID()[1]
                    _breaked = True
                    break

            if _breaked and _stateID != -2:
                self._states[_stateID].run()

    def addState(self, value=None):
        """Method that adds a state to the StateMachine
        """
        if type(value) is dict:
            _state = State()
            _state.initBySFF(value)
        elif type(value) is State:
            _state = value
        elif value is None:
            _state = State()
            _state.addAction(value)
        else:
            print("ERROR")

        self._states[_state.getID()] = _state

    def removeState(self, state_id:int):
        """Method which removes a state from the StateMachine
        """
        del self._states[state_id]

    def getStates(self):
        return self._states

    def addTransition(self, value=None):
        """Method that adds a Transition to the TransitionMachine
        """
        if type(value) is dict:
            _transition = Transition()
            _transition.initBySFF(value)
        elif type(value) is Transition:
            _transition = value
        elif value is None:
            _transition = Transition()
            _transition.addEvaluation(value)
        else:
            print("ERROR")

        self._transitions[_transition.getInOutID()] = _transition

    def removeTransition(self, transition_id:int):
        """Method which removes a Transition from the Transition Machine
        """
        del self._transitions[transition_id]

    def _checkStateMachineIntegrity(self):
        """Method that checks the integrity of the StateMachine
        """
        pass

    def _checkIntegrity(self):
        """Method that checks the JSON file integrity
        """
        if not os.path.isfile(self._data["path"]):
            print("ERROR")

        file_sm = open(self._data["path"], "r+")
        lines = file_sm.readlines()

        for s in self._data["StateMachine"]["State"].keys():
            if True not in ["def state_" + s in l for l in lines]:
                file_sm.write("def state_" + s +"():\n\t#TODO\n\tpass\n\n")

        for t in self._data["StateMachine"]["Transition"].keys():
            if True not in ["def transition_" + t in l for l in lines]:
                file_sm.write("def transition_" + t +"():\n\t#TODO\n\tpass\n\n")

        file_sm.close()

    def loadJSON(self, path: str):
        """Method that loads JSON file
        """
        json_file = open(path)
        self._data = json.load(json_file)
        json_file.close()

        self._checkIntegrity()

    def dumpJSON(self):
        """Method that saves StateMachine  to a JSON file
        """
        pass

    def __repr__(self):
        """Redefined method to print value of the StateMachine class instance

        Returns:
            str: printable value of StateMachine class instance
        """
        s = "State Machine name: " + self._name + "\n"

        for st in self._states.keys():
            s += self._states[st].__repr__() + "\n"

        for tr in self._transitions.keys():
            s += self._transitions[tr].__repr__() + "\n"

        return s
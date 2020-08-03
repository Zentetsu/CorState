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
'''


import json
import os


class StateMachine:
    """StateMachine class
    """
    def __init__(self, name: str):
        """Class constructor
        """
        self.name = name
        self.shared_var = []
        self.states = {}

        self.data = None

    def start(self):
        """Method that launches the state StateMachine
        """
        pass

    def add(self):
        """Method that adds a state to the StateMachine
        """
        pass

    def remove(self):
        """Method which removes a state from the StateMachine
        """
        pass

    def _checkIntegrity(self):
        """Method that checks the JSON file integrity
        """
        if not os.path.isfile(self.data["path"]):
            print("ERROR")

        file_sm = open(self.data["path"], "r+")
        lines = file_sm.readlines()

        for s in self.data["StateMachine"]["State"].keys():
            if True not in ["def state_" + s in l for l in lines]:
                file_sm.write("def state_" + s +"():\n\t#TODO\n\tpass\n\n")

        for t in self.data["StateMachine"]["Transition"].keys():
            if True not in ["def transition_" + t in l for l in lines]:
                file_sm.write("def transition_" + t +"():\n\t#TODO\n\tpass\n\n")

        file_sm.close()

    def loadJSON(self, path: str):
        """Method that loads JSON file
        """
        json_file = open(path)
        self.data = json.load(json_file)
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
        s = ""

        return s
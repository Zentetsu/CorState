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


class StateMachine:
    """StateMachine class
    """
    def __init__(self):
        """Class constructor
        """
        self.name = ""
        self.shared_var = []

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
        pass

    def loadJSON(self):
        """Method that loads JSON file
        """
        pass

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
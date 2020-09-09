'''
File: State.py
Created Date: Sunday, July 0th 2020, 12:13:46 am
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
2020-09-10	Zen	Refactoring the State structure
'''


from .CorStateError import *
from .Transition import Transition


class State:
    """State class
    """
    _nb_state = 0

    def __init__(self):
        """Class constructor
        """
        self._id = State._nb_state
        State._nb_state = State._nb_state + 1

        self._action = None

    def getID(self) -> int:
        """Method that returns State ID

        Returns:
            int: State ID
        """
        return self._id

    def initBySFF(self, sff:dict):
        """Method that initialzes state from a dict

        Args:
            sff (dict, optional): state from file.
        """
        pass

    def addAction(self, action):
        """Method that adds action to this state

        Args:
            action ([type]): action that will be executed by this state
        """
        self._action = action

    def run(self):
        """Method that will run the action defined to this state
        """
        self._action()

    def __repr__(self) -> str:
        """Redefined method to print value of the State class instance

        Returns:
            str: printable value of State class instance
        """
        s = "State id: " + str(self._id)

        return s
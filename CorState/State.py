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
'''


from .CorStateError import *


class State:
    """State class
    """
    nb_state = 0

    def __init__(self):
        """Class constructor
        """
        self.id = State.nb_state
        State.nb_state = State.nb_state + 1

        self.name = ""
        self.transitions = {}

        self.action = None

    def getID(self) -> int:
        """Method that returns State ID

        Returns:
            int: State ID
        """
        return self.id

    def __repr__(self) -> str:
        """Redefined method to print value of the State class instance

        Returns:
            str: printable value of State class instance
        """
        s = ""

        return s
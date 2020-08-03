'''
File: Transition.py
Created Date: Sunday, August 0th 2020, 5:46:20 pm
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


class Transition:
    """Transition class
    """
    nb_transition = 0

    def __init__(self):
        """Class constructor
        """
        self.id = Transition.nb_transition
        Transition.nb_transition = Transition.nb_transition + 1

        self.state_id = []
        self.name = ""

        self.action = None

    def getID(self) -> int:
        """Method that returns Transition ID

        Returns:
            int: Transition ID
        """
        return self.id

    def __repr__(self) -> str:
        """Redefined method to print value of the Transition class instance

        Returns:
            str: printable value of Transition class instance
        """
        s = ""

        return s
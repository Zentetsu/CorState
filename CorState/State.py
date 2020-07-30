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
    def __init__(self):
        """Class constructor
        """
        self.name = ""
        self.cur_state = None
        self.time = None
        self.first = False

    def start(self):
        pass

    def _enterAction(self):
        pass

    def _exitAction(self):
        pass

    def _readValue(self):
        pass

    def _writeValue(self):
        pass

    def __repr__(self):
        """Redefined method to print value of the State class instance

        Returns:
            str: printable value of State class instance
        """
        s = ""

        return s

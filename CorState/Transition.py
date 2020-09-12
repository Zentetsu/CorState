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
2020-09-12	Zen	Updating some comments
2020-09-11	Zen	Updating import module
2020-09-10	Zen	Refactoring the Transition structure
'''


from .CorStateError import *
import os


class Transition:
    """Transition class
    """
    _nb_transition = 0

    def __init__(self):
        """Class constructor
        """
        self._id = Transition._nb_transition
        Transition._nb_transition = Transition._nb_transition + 1

        self._ioID = None
        self._evaluation = None

    def getID(self) -> int:
        """Method that returns Transition ID

        Returns:
            int: Transition ID
        """
        return self._id

    def initByTFF(self, tff:dict, module:[str, str]):
        """Method that initialzes a Transition from a JSON file

        Args:
            tff (dict): state from file
            module ([type]): module information
        """
        module_dir, module_file = os.path.split(module[1])
        module_name, module_ext = os.path.splitext(module_file)
        # save_cwd = os.getcwd()
        # os.chdir(module_dir)
        module_obj = __import__(module_name)
        module_obj.__file__ = module[1]
        globals()[module_name] = module_obj
        # os.chdir(save_cwd)
        # self.mod = importlib.import_module(module[0], module[1])
        # globals().update(mod.__dict__)

        self._id = tff["id"]
        self._ioID = (tff["id_in"], tff["id_out"])
        self._evaluation = getattr(module_obj, tff["evaluation"])

    def setInOutID(self, ini:int, outi:int):
        """Method that initializes the in and out state id

        Args:
            ini (int): in state id
            outi (int): out state id
        """
        self._ioID = (ini, outi)

    def getInOutID(self) -> (int, int):
        """Method that returns the in and out state id

        Returns:
            (int, int): tuple of in and out state id
        """
        return self._ioID

    def addEvaluation(self, evaluation):
        """Method that evaluates a condition to allow the State Machien to move to the next state

        Args:
            evaluation ([type]): Function called to evaluate the possibilite to move to the next state
        """
        self._evaluation = evaluation

    def evaluate(self) -> bool:
        """Meyhod that runs the evalaute function

        Returns:
            bool: Evaluation result
        """
        return self._evaluation()

    def __repr__(self) -> str:
        """Redefined method to print value of the Transition class instance

        Returns:
            str: printable value of Transition class instance
        """
        s = "Transition id: " + self._id.__repr__() + "; (in, out): " + self._ioID.__repr__()

        return s
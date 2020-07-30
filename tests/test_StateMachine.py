'''
File: test_StateMachine.py
Created Date: Sunday, July 0th 2020, 12:17:58 am
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


from context import State, Machine
from CorState.State import State
from CorState.Machine import Machine

def test_createInstance():
    print("Create Instance:", end=" ")
    try:
        sm = State()
        print("SUCCESSED")
        assert True
    except:
        print("FAILED")
        assert False

print("-"*10)
test_createInstance()
print("-"*10)
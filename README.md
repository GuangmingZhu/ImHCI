## Contents
1.[Software](#Software)
2.[Data Format Description](#Data-Format-Description)
3.[Algorithm](#Algorithm)

### <span id="Software">
## Software
**Development  Environment**
* qt creator 4.3.0
* visual studio 2019
* win 10

**Additional libraries used:**
* zmq（for process communication）



----

### <span id="Data-Format-Description">
## Data Format Description
The data set was collected by 20 testers, and each tester collected 28 groups of data.

The data records the gazing point and mouse operation of each tester in each group of operations

Each csv file records the data of the tester in the experiment. All values are separated via comma(,), each row corresponds to one data record . 
The 5 columns represent:
|  Name   |  Description   |
| :-: | :-: |
|  Timestamp   |  The timestamp of the record   |
|  GazeX   |  X axis coordinate of the user's gaze point on the screen coordinate system   |
|  GazeY   |  Y axis coordinate of the user's gaze point on the screen coordinate system   |
|  MouseX   |   The X coordinate of the computer mouse cursor on the screen  |
|  MouseY   |  The Y coordinate of the computer mouse cursor on the screen   |
|  Operation   |   The user's current mouse operation event. Integer (0,1,2,3) indicating indicates different click events. 0 indicates that the left mouse button is pressed, 1 indicates that the right mouse button is pressed, 2 indicates that the middle mouse button is pressed, and 3 indicates that no key is pressed  |

----

### <span id="Algorithm">
## Algorithm
The algorithm file mainly contains three algorithm files corresponding to the three algorithms in the paper

**Runing  Environment**
* win10
* Python 3.7
* RTX 2060 GPUs

----

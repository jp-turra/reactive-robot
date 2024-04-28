# Mobile Robot with Basic Reactive Behavior

## Setting up Arduino IDE
* Copy the folder "Robotica_Movel" from "Libraries" and paste it on the Library folder of Arduino IDE (~/Documents/Arduino/libraries).
* Clone the repository [IRremote](https://github.com/Arduino-IRremote/Arduino-IRremote?tab=readme-ov-file#how-we-decode-signals) as Zip file and import it to Arduino IDE.

## Usage
* IR Controller
  * `IR_KEY_1`: Start the reactive behavior
  * `IR_KEY_OK`: Stop the robot and set the manual mode
  * `IR_KEY_UP`: Move the robot forward if in manual mode
  * `IR_KEY_DOWN`: Move the robot backward if in manual mode
  * `IR_KEY_LEFT`: Turn the robot left if in manual mode
  * `IR_KEY_RIGHT`: Turn the robot right if in manual mode

# License

This project is licensed under the terms of the GNU General Public License. See the file "LICENSE" for details.
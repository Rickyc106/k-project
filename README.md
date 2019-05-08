# Welcome to UTME Team Hood (K Project) Repo!
The following project was sponsored by The University ofTexas at Austin's Mechanical Engineering Department (UTME). This project was created using open source packages granted free of charge according to relevant MIT licensing.

This repo contains the following:
- Main Arduino source
- Supporting Arduino Librarires utilized by the main Arduino source
- Python scripts to verify systems are operational

# Initial Setup
To set up the Arduino Environment install the Integrated Devlopement Environment (IDE) from the official [Arduino website](https://www.arduino.cc/en/Main/Software).

Once the IDE has been installed navigate to the libraries folder. This folder will normally be located within the main Arduino folder on your desktop.

Copy the corresponding library folders (maintaining file structure) into the local Arduino Libraries folder. These librarires include:
- ArduinoJSON
- EasyUdp

Once finished you may open the sendJSONoverUDP.ino file within in the Arduino IDE. Click compile in the top left (green check mark) to ensure the corresponding libraries have been sourced properly.

And... that's it! You are ready to use the Arduino to communicate over JSON utilizing UDP.

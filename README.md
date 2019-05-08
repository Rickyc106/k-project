# Welcome to UTME Team Hood (K Project) Repo!
The following project was sponsored by The University of Texas at Austin's Mechanical Engineering Department (UTME). This project was created using open source packages granted free of charge according to relevant MIT licensing.

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

Once finished you may open the sendJSONoverUDP.ino file within the Arduino IDE. Click compile in the top left (green check mark) to ensure the corresponding libraries have been sourced properly.

And... that's it! You are ready to use the Arduino to communicate over UDP utilizing JSON documents.

# Examples
Example code utilizing the EasyUdp library can be found within the examples directory within EasyUdp. This program requires you to provide a simple analog signal (any potentiometer will work), connected to the A0 pin.

Additionally, you must modify the IP address, local port, and Arduino mac address witihn the example program to ensure your test will function as intended. By default these parameters have already been populated, however the IP address will almost always be unique to YOUR network.

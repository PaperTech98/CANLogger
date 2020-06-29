CAN or Controller Area Network is a data transmission protocol used to reliably 
transmit small packets of data in a high noise environment. CAN is commonly 
used in Automotive applications to allow for communication between onboard 
electrical control units and sensors. 

The Goal of this project is to create a framework for custom applications to 
access and transmit CAN data as a node in a CAN network. This framework has 
been designed to allow for maximum flexibility and for programs to be created 
with minimal knowledge of the CAN protocol by using a high level of abstraction 
when requesting a data stream. This framework once complete is intended to be 
used for a custom digital instrument cluster on an NA Miata currently undergoing 
extensive modification. 

The default XML data being provided uses the Haltech CAN Broadcast Protocol v2.
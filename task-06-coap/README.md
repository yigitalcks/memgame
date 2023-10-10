Task 06: Exposing and Using Hardware Via CoAP
=============================================

General Understanding
---------------------

The following documentations will be useful:

1. [The gcoap API](https://api.riot-os.org/group__net__gcoap.html)
1. [The nanocoap API](https://api.riot-os.org/group__net__nanocoap.html)
1. [The Wikipedia article on REST](https://en.wikipedia.org/wiki/Representational_state_transfer)
1. [The phydat API](https://api.riot-os.org/group__sys__phydat.html)
1. [The IANA registry of CoRE Parameters](https://www.iana.org/assignments/core-parameters/core-parameters.xhtml)

Answer the following questions:

1. How can one request the board name via CoAP with the given template?
1. What CoAP request method makes most sense for reading a SAUL sensor remotely?
1. What format makes most sense to represent a SAUL reply, as it is flexible, human and machine readable, and easy to implement? (Hint Content Format 50)

The Programming Task
--------------------

1. Extend the provided template so that one CoAP URI path is registered per SAUL device
    - The paths should be named "/saul/<ID>", where ID can be the name or the number of the device
1. The resources should support the methods GET and PUT
1. A GET request results in the given SAUL endpoint being read and responds with the sensor data in a sensible format
1. A PUT request results in the provided payload being written to the given SAUL endpoint
    - It is absolutely fine to only support 1-dimensional data, e.g. encoded as string containing decimal digits only
    - You can use proper encodings like CBOR or JSON.
        - For both libraries are supported in RIOT via packages
        - Keep in mind that the provided example client will need to be extended to actually use this interface
        - Bottom line: Go with 1-dimensional data

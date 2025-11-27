

1\. Start marker (STX, 0x02)

● Even if noise appears before, Python ignores it until it sees STX.

2\. Request code (REQ, 0x05)

● Let Python explicitly ask for data, instead of Arduino spamming nonstop.

● This avoids overwhelming the serial buffer..

● Also useful if Arduino could handle multiple request types later (eg 0x05 = sensor data,

0x06 = configuration).

3\. End marker (ETX, 0x03)

● Even if Python didn’t know how long the message was, it knows exactly where to stop

reading.


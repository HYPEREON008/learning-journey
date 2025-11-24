import tkinter as tk
from tkinter import ttk #themed tkinter for better looks
import time
import serial

serialPort = ''  # OS portname for arduino 
baudRate = 9600 # Update this to your baud rate which is set in Arduino IDE and is equivalent to signal changes per sec
try: 
    ser = serial.Serial(serialPort, baudRate, timeout=1) #setup serial connection
    time.sleep(2) # wait for the serial connection to initialize
except Exception as e:
    ser = None
    print("Could not open serial port.")

def requestData():
    if ser: #connection initialised
        ser.write(bytes([2, 5, 3])) #request data command
        time.sleep(0.1) #wait for arduino to process command
        #freezes the screen so use root.after method instead

        if ser.in_waiting > 0:
            line = ser.read_until(b'\x03')
            line = line.decode(errors = "ignore") #decodes byte to string
            #to prevent unicodeDecodeError from occuring in case of noise etc
            #makes python discard any characters that cannot be decoded using the specified encoding

            try:
                values = line.replace("\x02", "").replace("\x03", "").replace("\x05", "")#removes start byte and end byte and req byte
                values = values.strip() #removes any whitespace characters
                readings = values.split(",") #splits the string into a list of readings
                if len(readings) >= 4: # Check if we have all four readings

                    #change the StringVar obj values to update the GUI
                    temp.set(readings[0])
                    pressure.set(readings[1])
                    flowRate.set(readings[2])
                    rpm.set(readings[3])

            except Exception as e:
                print(f"Error processing data: {e}")
    root.after(1000, requestData) #keep requesting data after 1 second(does not block, just sets up a timer)
 
# GUI design (window setup)
root = tk.Tk() #sets up an object of Tk class which is the root window
root.title("Engine Monitoring System") #of the window (in top bar)
root.geometry("800x500")
root.resizable(False, False)  #fixed size window (unresponsive/non-resizable)

#pack grid place are geometry managers to position the frames and labels inside the window
#we aare using pack and grid
#pack stacks widgets vertically from top to bottom of window


# Title label
title_label = tk.Label(root, text="ENGINE SENSOR READINGS", font=("Arial", 28, "bold"))
title_label.pack(pady=20)

# Frame for inputs
frame = ttk.Frame(root, padding=40)  #unresponsive frame so absolute padding  
frame.pack(fill="both") #frame fills whole window
#frames are a container for other widgets, helps in organizing the layout

# Tkinter StringVars(obj) for sensor values
temp = tk.StringVar()
pressure = tk.StringVar()
flowRate = tk.StringVar()
rpm = tk.StringVar()

# Labels + Entry boxes
labels = ["Temperature (°C)", "Pressure (Pa)", "Fuel Flow (L/min)", "RPM"]
vars = [temp, pressure, flowRate, rpm]

for i, (labl, var) in enumerate(list(zip(labels, vars))): #zip returns a zip obj with pairs of elements from both lists
    #list is unnecessary here but helps me understand
    #Enumerate adds a counter to an iterable and returns it in a form of enumerating object

    #parent of the label is the Frame "frame"
    L= ttk.Label(frame, text=labl, font=("Arial", 22)) #creates label object
    L.grid(row=i, column=0, pady=10, sticky="w") #sticky aligns the label to the west(left)
    E= ttk.Entry(frame, textvariable=var, width=20, font=("Arial", 22)) #creates entry object
    E.grid(row=i, column=1, pady=10) #pady adds vertical padding above and below the widget(10pixel)
# START
requestData()
root.mainloop() #tkinters event loop initiated, draws widgets created keeps window open and listens for events,

# Welcome to the Embedded Meetup

Welcome to the meetup! Today, the goal will be to write code that will be run on a Real-Time Operating System (RTOS) and will control the hardware.

## Project Objective
Your objective is to write code for an ESP32 microcontroller which should control three LEDs and a 3-unit 8x8 LED Matrix display.

### Pinout and Peripherals
As for any software embedded project, you will need a pinout and a description of the connected peripherals.

#### Digital Output LEDs
The LEDs should be controlled by the following digital output pins:
* **Red LED:** Pin D14
* **Yellow LED:** Pin D12
* **Green LED:** Pin D13

#### 8x8 LED Matrix Display
Three segments of 8x8 LED matrix display are connected on SPI (Serial Peripheral Interface), which uses several wires for communication:
* **CLK (Clock):** Pin D18
* **MOSI (Master Output - Slave Input):** Pin D19

Since the bus can handle multiple devices connected, there is a chip select pin:
* **CS (Chip Select):** Pin D5

Today you don't need to worry about this part, since the ESP-IDF environment provides a driver for SPI, and we will also be using a library for the MAX7219 thanks to an open-source project. Otherwise, depending on the platform, making these libraries would be part of the everyday work of an embedded developer. In the start code, SPI and MAX7219 are initialized and ready to use.

### Software Architecture: RTOS
To make your life easier, we will of course use an operating system, but one made for real-time systems: RTOS. 

#### Execution Structure
In the starting code, you can find an **init runnable** that will be called at controller boot-up. The rest of the implementation should be written in **runnables** that can be called from two provided tasks:
1. 10ms Task: This task has the highest priority.
2. 20ms Task: This task has a lower priority.

### Important Development Rules
Keep in mind that you should write your code in a way that the lowest priority task, which controls the onboard "Alive" LED, should still be executed. 
* Your runnables should not take too much execution time.
* Your code should not use blocking functions. 
* Blocking or long execution times will prevent other parts of the system from running, and the "Alive" LED will stop blinking, or blinking frequency will be affected.

## Expedition Tools & Commands

To navigate this project, you will mainly interact with the ESP-IDF extension via the VS Code status bar at the bottom or the Command Palette.

### Essential Actions
* **Build (Cylinder Icon):** Compiles your code.
* **Flash (Lightning Icon):** If you are using real hardware, this sends your compiled program to the ESP32.
* **Monitor (Plug Icon):** Opens the terminal to see serial output.
* **Wokwi Simulator:** Open `diagram.json`. If the project is built, the simulator starts automatically and shows the terminal output on the side.

### Debugging with ESP_LOGI
In embedded development, we do not have a standard "console" for printing. Instead, we use the `ESP_LOGI` macro to send information back to your computer via the serial port. The terminal will display your messages in real-time, color-coded by the log level. This is the primary way to check if your counters are incrementing correctly or if your state machine is switching as expected.

To see what is happening inside your code, use the following syntax:
`ESP_LOGI("TASK_NAME", "Current count: %d", counter_variable);`

## Challenge 1: Hello (Embedded) World

The first milestone of any hardware journey is making an LED blink. For this task, your goal is to make the red LED on pin **D14** blink at a frequency of **1 Hz**, meaning it should be on for 500ms and off for 500ms.

Since we are working with an RTOS, there is a catch: you cannot use a standard "delay" or "sleep" function. If you tell the processor to wait, you will block the entire system, and the onboard alive LED will stop blinking. Instead, you need to use the provided 10ms or 20ms tasks as your heartbeat. 

**DoD:** The Red LED blinks steadily while the "Heartbeat" LED continues to flicker.

## Challenge 2: The Traffic Light Controller

Now that you have control over a single LED, it is time to manage all three. Your objective is to create a logic that mimics a standard traffic light sequence using the **Red (D14)**, **Yellow (D12)**, and **Green (D13)** LEDs.

The system must follow this specific loop:
1. **Red phase:** The Red LED is active for several seconds.
2. **Preparation phase:** Both Red and Yellow LEDs are active simultaneously.
3. **Green phase:** The Green LED is active for several seconds.
4. **Green transition:** The Green LED must blink exactly 5 times.
5. **Yellow phase:** The Yellow LED is active for a brief period before the loop restarts.

You are responsible for determining the specific duration of the Red and Green phases. Ensure they are long enough to allow for future tasks involving the LED matrix. The logic must reside within the existing task structure, ensuring the "Alive" LED remains functional throughout all transitions.

**DoD:** A smooth, looping traffic light sequence that handles the "Blinking Green" logic correctly.

## Challenge 3: The Matrix Awakens

Now that your traffic light sequence is running, it is time to bring the visual element into play. Your next objective is to draw a custom image or symbol across the three 8x8 LED matrix segments. This will require you to interface with the MAX7219 driver that has been pre-initialized in your starter code.

To create your visual, you can use an online tool like the [LED Matrix Editor](https://xantorohara.github.io/led-matrix-editor/). Use the editor to design a bitmap that fits the 24x8 resolution of your display. Once you have your design, you will need to take the generated hex or byte arrays and integrate them into your code to be drawn onto the display using the available library functions.

The main requirement for this challenge is that your traffic light system from Challenge 2 must continue to function perfectly in the background. The matrix display should show your custom design while the LEDs continue their Red-Yellow-Green cycle without any interruption.

## Challenge 4: The Great Shift

With a static image successfully appearing on the display, the next step is to introduce motion. Your goal for this challenge is to take the bitmap or symbol you created in the previous step and make it shift or scroll across the 24x8 matrix area.

You will need to decide on a desired speed for this movement. Since your code is executed within the 10ms and 20ms tasks, you must determine how frequently the image data should be shifted to create a smooth animation. As with the previous tasks, the traffic light sequence must remain fully operational and synchronized while the matrix animation is running.



## Challenge 5: Context-Aware Signage

For the final milestone, you will transform the LED matrix into a dynamic "Smart Sign" that reacts to the state of your traffic light controller. The display should now provide different information depending on which light is active.

Your objectives for this final task are:
1. **Red Light Active:** The matrix should display a descriptive text string or a custom symbol (such as a STOP icon). 
2. **Green Light Active:** The matrix must switch to displaying shifting arrows (e.g., `-> -> ->`) that move from left to right to guide traffic through the intersection.

You must ensure that the transition between these displays happens automatically as the traffic light changes phases. Make sure the durations you set for your Red and Green phases in Challenge 2 provide enough time for the scrolling text or arrows to be clearly readable by an observer.
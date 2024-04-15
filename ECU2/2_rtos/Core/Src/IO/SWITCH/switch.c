#include "IO/SWITCH/SWITCH.h"

void Switch_Init(void) {
    // GPIO initialization code specific to your setup
}

// Check and return the state of the button
// About LCD BUTTON
uint8_t Switch_GetState1(void) {
    static uint8_t prevButtonState = GPIO_PIN_SET; // Assume button is not pressed initially
//    uint8_t buttonState = HAL_GPIO_ReadPin(sideMirror_Joystick_Switch_GPIO_Port, sideMirror_Joystick_Switch_Pin); // Read the current button state
    uint8_t buttonState = HAL_GPIO_ReadPin(test_SW_GPIO_Port, test_SW_Pin); // Read the current button state

    if(buttonState == GPIO_PIN_RESET && prevButtonState == GPIO_PIN_SET) {
        // Button was just pressed
        prevButtonState = buttonState; // Update the previous button state
        return 1; // Return 1 to indicate button press
    } else {
        // Update the previous button state
        prevButtonState = buttonState;
        return 0; // Return 0, button not pressed
    }
}

// Check and return the state of the button
// About HeadLight Button
uint8_t Switch_GetState2(void) {
    static uint8_t prevButtonState = GPIO_PIN_SET; // Assume button is not pressed initially
    uint8_t buttonState = HAL_GPIO_ReadPin(headLight_SW_start_GPIO_Port, headLight_SW_start_Pin); // Read the current button state
//    uint8_t buttonState = HAL_GPIO_ReadPin(test_SW_GPIO_Port, test_SW_Pin); // Read the current button state

    if(buttonState == GPIO_PIN_RESET && prevButtonState == GPIO_PIN_SET) {
        // Button was just pressed
        prevButtonState = buttonState; // Update the previous button state
        return 1; // Return 1 to indicate button press
    } else {
        // Update the previous button state
        prevButtonState = buttonState;
        return 0; // Return 0, button not pressed
    }
}


# Create & Test

## Embedded Dice Device Functionality Test

#### Test Case ID: 1

### Preconditions:

1. The embedded dice device is properly connected to the webpage.
2. The webpage is accessible and functional.
3. Users have valid session on the webpage.

### Test Steps:
1. **Initialization:**

    1. Open the webpage on a compatible browser.
    2. create a valid session.


2. **Roll Dice Functionality:**

    1. Click on the "Roll Dice" button on the webpage.
    2. Verify that the dice animation starts indicating the rolling process.
    3. After a reasonable delay, verify that the animation stops, and a number is displayed indicating the result of the dice roll.
    4. Ensure that the number displayed is within the valid range for a standard die (1 to 6).

3. **Verify Result Consistency:**

    1. Repeat step 3 multiple times (at least 5 times) and ensure that each time the result varies randomly within the valid range.
    2. Verify that the results are consistent and do not display any patterns or biases.

4. **Multi-User Interaction:**

    1. Open another browser window or use a different device to create a new session.
    2. Simultaneously, both users attempt to roll the dice.
    3. Verify that each user receives an independent and random result for their dice roll.
    4. Ensure that the dice roll for one user does not interfere with the dice roll of another user.


### Expected Results:

1. The webpage loads successfully, and the user is able to log in without any errors.
2. The "Dice Rolling" section is accessible, and the embedded dice device is visible.
3. When the "Roll Dice" button is clicked, the animation starts, and after a delay, a random number between 1 and 6 is displayed.
4. The dice rolls are consistent, random, and do not display any biases.
5. Multiple users can independently roll the dice without interference from each other.


## Test Results

### Tester 1
1. user did not copy the MAC address from the captive page so he does not know the device_id
2. Device is visible but user complains that the roll button is not visible and he has to scroll down.
3. This part worked correctly!
4. This part works correctly !
5. The dice mediately starts continuing rolling after another player pressed on roll showing the rolled dice for a very short time.

### Tester 2
1. user filled in the wrong ssid or password but did not know which one was wrong, eventually the user did copy the MAC address and logged in correctly.
2. dice was already rolling after logging in
3. This part worked correctly!
4. This part works correctly !
5. The dice rolls of users do not interfere but it is not easy to tell who rolled the dice.
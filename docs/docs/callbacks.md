# Lua Callbacks

## isKeyDown(keyCode)

#### Parameters

* keyCode: A String corresponding to a key

#### Return Value

* A boolean value corresponding to whether or not the key is pressed
    
Checks to see if the given key is currently pressed

    if isKeyDown("KEY_LEFT") {
        print("Key is down")
    }
    
## forceKeyUp(keyCode)
    
#### Parameters

* keyCode: A String corresponding to a key
    
#### Return Value

* N/A
    
Marks a key as not being pressed. This can be used to make sure the key only registers as pressed for one frame.

This will stop working once the key goes into repeat mode.

    if isKeyDown("KEY_LEFT") {
        forceKeyDown("KEY_LEFT")
        print("Key is down")
    }
    
## getMousePos()

#### Parameters

* N/A
    
#### Return Value

* A table holding the mouse position with the indices X and Y

Retrieves a table holding the mouse position with the indices X and Y

    mousePos = getMousePosition()
    print("MouseX: " .. mousePos["X"])
    print("MouseY: " .. mousePos["Y"])
    
## setMousePos(mousePos)

#### Parameters

* mousePos: A table holding the mouse position with the indices X and Y
    
#### Return Value

* N/A

Changes the mouse position to the values from the parameter

    mousePos = {X = 50, Y = 75}
    setMousePos(mousePos)
    
## getTime()

#### Parameters

* N/A

#### Return Value

* The current time in milliseconds

Retrieves the the current time in milliseconds

    time = getTime()
    
## quitGame()

#### Parameters

* N/A

#### Return Value

* N/A

Cleans up and closes the game process. Game closes after the function which called quitGame returns

    if isKeyDown(KEYCODE["KEY_ESCAPE"]) then
        quitGame()
        return
    end
    
## getScreenWidth()

#### Parameters

* N/A

#### Return Value

* The width of the current window in pixels

Retrieves the width of the game windows in pixels (whole number)

    screenWidth = getScreenWidth()

## getScreenHeight()

#### Parameters

* N/A

#### Return Value

* The height of the current window in pixels

Retrieves the height of the game windows in pixels (whole number)

    screenWidth = getScreenHeight()
    
## getDeltaTime()

#### Parameters

* N/A

#### Return Value


* The amount of time that passed since the last frame (milliseconds/frame)

Retrieves how many milliseconds pass between frames

    x = 10
    deltaTime = getDeltaTime()
    x = x + (5 * deltaTime)
    
## isColliding()

#### Parameters

* N/A

#### Return Value

* A table holding an identifier for which objects this ojbect is colliding with. Does not include itself.

Retrieves a list of objects that this object is colliding with. The list does not include this object.

    collision = isColliding()
    if tableLength(collision) > 0 then
        for _,value in ipairs(collision) do
            if compareTag(value, "Goal") == 1 then
                loadScene(2)
            end
        end
    end
    
## collisionDirection(objectIdentifier)

#### Parameters

* objectIdentifier: An object identifier representing an object to get the direction toward

#### Return Value

* A table representing the direction to the object passed in with the indices X and Y.

#### Errors

* Invalid object identifier: A table with 0 for both the X and Y direction will be returned

This function does not check for collision. It just gives the direction.

    if tableLength(collision) > 0 then
        for _,value in ipairs(collision) do
            collisionDir = collisionDirection(value)
            print("collisionXDir: " .. collisionDir["X"])
            print("collisionYDir: " .. collisionDir["Y"])
        end
    end
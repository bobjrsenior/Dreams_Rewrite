# Lua Callbacks

## getTime()

Retrieves the the current time in milliseconds

    time = getTime()
    
## Keyboard and Mouse Callbacks

### isKeyDown(keyCode)
    
Checks to see if the given key is currently pressed

    if isKeyDown("KEY_LEFT") {
        print("Key is down")
    }
    
### forceKeyUp(keyCode)
    
Marks a key as not being pressed. This can be used to make sure the key only registers as pressed for one frame.

This will stop working once the key goes into repeat mode.

    if isKeyDown("KEY_LEFT") {
        forceKeyDown("KEY_LEFT")
        print("Key is down")
    }
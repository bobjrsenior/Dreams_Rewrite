livesUIIndex = -1
livesInit = 0

function update()

    if livesInit == 0 then
        livesInit = 1
        livesUIIndex = addUIText("Lives: 3", 10, 0)
    end
    
    lives = getGlobalNumber("Lives")
    if lives ~= lives then
        addGlobalNumber("Lives", 3)
    end
    
    modifyUIText(livesUIIndex, "Lives: " .. lives)
end
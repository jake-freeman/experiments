numbers = [1,2,3,4,5]
pb = 6

prizes    = [0,0,4,7,100,1000000]
prizes_pb = [4,4,7,100,50000,1600000000]

puts 'Enter amount of money in dolars'
money = gets.chomp.to_i
won = 0
spent = 0

balls = (1..69).to_a

i = 0
while money > 2
    i += 1
    powerball = 1 + rand(26)
    pick = balls.shuffle[0..4].sort
    money -= 2
    spent += 2

    #puts pick
    #puts powerball

    matches = (numbers & pick).size
    pb_match = (pb == powerball)
    #puts "Matches: #{matches}"
    #puts "PB match: #{pb_match}"
    #puts

    if (pb_match)
        prize = prizes_pb[matches]
    else
        prize = prizes[matches]
    end

    won   += prize
    money += prize

    if (won > 1000000000)
        puts "Jackpot!"
        puts "Money Spent: $#{spent}"
        puts "Money Won:   $#{won}"
        puts
        break
    end

    if (i > 10000)
        i = 0
        puts "Money left:  $#{money}"
        puts "Money Spent: $#{spent}"
        puts "Money Won:   $#{won}"
        puts "Net Gain:    $#{won - spent}"
        puts
    end

end

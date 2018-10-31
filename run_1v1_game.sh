#!/bin/bash

echo tournament_1v1/*.txt > temp.txt

cat temp.txt | sed "s/ /\n/g" > temp_2.txt

rm temp.txt


text="place_holder"

until ["$text" eq ""]; do
    text=$(head -n 1 temp_2.txt)
    cp $text ./config.txt
    ./platform
    #Fun fact! putting a '>>' in the command below will fill up your hard drive 
    # and crash your system.... or so i've heard.... -R
    tail -n +2 temp_2.txt > temp_2.txt
done

rm temp_2.txt    
    



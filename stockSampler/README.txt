Read Me Stocksampling

So there is a bunch of stuff in this file.
1.Date/Calander/Time managment
2.Data struct for stockNodes
3.Actual sampling of the stockNodes

Currently the sampling method is linear. There is equal space between each sample
A uncertainty is calculated for each value. The data is then all entered into a stockNode vector for easy usage.
The stockNodes in the vector have a getNext() function. Do not use this, it is just a redundant feature that I have carried over from the actual data structure
To itterate through the values use the regular vector[] method.

Do not worry about the date and etc management if there is an issue with it please message me. The math is accurate as far as I know.
While the math is accurate it is not fast. It does how ever make sure you have the correct number of days per month and accounts for leap years.

The data sampling takes known nodes and enters them into a list. These values are then sampled with linear interpolation if the date you want does not precisely hit a node.

In the main there is a setup that works.
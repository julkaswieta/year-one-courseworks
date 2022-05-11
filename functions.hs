-- QUESTION 1: Sets -- 

-- removes duplicates from a list 
duplicateFree' :: (Eq a) => [a] -> [a]
duplicateFree' [] = [] 
duplicateFree' (x:xs) 
    | elem x xs = duplicateFree' xs
    | otherwise = x : duplicateFree' xs

-- combines a list of list into a single list
union' :: [[a]] -> [a]
union' [] = []
union' (xs:xss) = xs ++ union' xss

-- returns a union of lists in a list 
bigUnion :: (Eq a) => [[a]] -> [a]
bigUnion xss = duplicateFree' (union' xss)

-- returns a list of partial sums of a list  
partialSums :: [Int] -> [Int]
partialSums [] = []
partialSums [x] = [x]
partialSums (x:xs) = x : (map (+x) (partialSums xs)) 

-- returns the index of an element in a list 
-- starting index is 1 
getIndex' :: Int -> [Int] -> Int
getIndex' y [x] = 1
getIndex' y (x:xs) 
    | y == x = 1
    | otherwise = 1 + getIndex' y xs 

-- returns the index of an element at which the partial sum is maximised 
maxIndex :: [Int] -> Maybe Int
maxIndex [] = Nothing
maxIndex xs = Just (getIndex' (maximum (partialSums xs)) (partialSums xs))


-- TEST SET FOR Q1
{-
Your functions should have the following behaviour:

bigUnion [[1,2,3],[3,4,5],[2,4,6,8]] = [1,2,3,4,5,6,8]
bigUnion ["list a", "list b"] = "list ab"
 
THE ORDER OF ELEMENTS IN THE RESULTS bigUnion IS NOT IMPORTANT.

partialSums [1,2,3,4,5] = [1,3,6,10,15]
partialSums [-1,1,-1,1,-1] = [-1,0,-1,0,-1]

maxIndex [1,2,3,4,5] = Just 5
maxIndex [-1,1,-1,1,-1] = Just 2

-}



-- QUESTION 2: Functions and relations -- 

-- returns a list of all first elements from a list of pairs 
allFst' :: [(a,b)] -> [a]
allFst' [] = []
allFst' (x:xs) = fst x : allFst' xs

-- returns a list of all second elements from a list of pairs 
allSnd' :: [(a,b)] -> [b]
allSnd' [] = []
allSnd' (x:xs) = snd x : allSnd' xs

-- returns a unique set of all inputs 
allArguments' :: [((Int, Int), Int)] -> [Int]
allArguments' xss = duplicateFree' (allFst' (allFst' xss) ++ allSnd' (allFst' xss))

-- takes a list of inputs, and creates binary identity functions from them
makeIdentity' :: [a] -> [((a,a),a)]
makeIdentity' [] = []
makeIdentity' (x:xs) = ((x,x),x) : makeIdentity' xs

-- reverses the order of inputs, eg. ((a,b),c) becomes ((b,a),c)
reverseArguments' :: [((Int,Int),Int)] -> [((Int,Int),Int)]
reverseArguments' [] = []
reverseArguments' (xs:xss) = ((snd (fst xs), fst (fst xs)), snd xs) : reverseArguments' xss 

-- returns the smallest function that is a commutative extension of the initial function 
makeCommutative :: [((Int,Int),Int)] -> [((Int,Int),Int)]
makeCommutative xss = duplicateFree' (xss ++ makeIdentity' (allArguments' xss) ++ reverseArguments' xss)

-- returns everything that is related to element a by the relation xs
oneHop :: (Eq a) => a -> [(a,a)] -> [a]
oneHop y [] = []
oneHop y (x:xs) 
    | fst x == y = snd x : oneHop y xs
    | otherwise = oneHop y xs

-- returns all possible paths through a relation that are 1 step longer than the specified one
nextSteps :: (Eq a) => [a] -> [(a,a)] -> [[a]]
nextSteps ps [x] = []
nextSteps ps (x:xs)
    | last ps == fst x = (ps ++ [snd x]) : nextSteps ps xs
    | otherwise = nextSteps ps xs

allElementsReachable :: (Eq a) => Int -> a -> [(a,a)] -> [a]
allElementsReachable n x rs = error "You've not tried to write allElementsReachable yet"


-- TEST SET FOR Q2
{-
Your functions should have the following behaviour:

makeCommutative [((1,2),3),((3,2),5),((1,4),0)] = 
    [((2,1),3),((2,3),5),((4,1),0),((1,2),3),((3,2),5),((1,4),0),((3,3),3),((1,1),1),((2,2),2),((4,4),4)]
    
makeCommutative [((4,1),0)] =
    [((1,4),0),((4,1),0),((4,4),4),((1,1),1)]

oneHop 3 [(1,3),(3,2),(3,4),(3,1),(2,3),(1,4)] = [2,4,1]
oneHop 1 [(1,3),(3,2),(3,4),(3,1),(2,3),(1,4)] = [3,4]

DO NOT WORRY ABOUT THE ORDER OF THE ELEMENTS IN THE RETURN LIST FOR oneHop

nextSteps [1,3] [(1,3),(3,2),(3,4),(3,1),(2,3),(1,4)] = [[1,3,2],[1,3,4],[1,3,1]]
nextSteps [3,4] [(1,3),(3,2),(3,4),(3,1),(2,3),(1,4)] = []

DO NOT WORRY ABOUT THE ORDER OF THE ELEMENTS IN THE RETURN LIST (i.e. THE ORDER THE LISTS APPEAR IN THE LIST OF LISTS)

allElementsReachable 2 1 [(1,3),(3,2),(3,4),(3,1),(2,3),(1,4)] = [2,4,1]
allElementsReachable 6 4 [(1,3),(3,2),(3,4),(3,1),(2,3),(1,4)] = []

DO NOT WORRY ABOUT THE ORDER OF THE ELEMENTS IN THE RETURN LIST FOR allElementsReachable

-}



-- QUESTION 3: Primes --

-- checks if n is a factor of m (m divides n with no reminder)
divides :: Int -> Int -> Bool
divides m n = rem m n == 0

-- checks if n is a composite number 
isComposite :: Int -> Bool
isComposite n = foldl (||) False (map (divides n) [2..(n-1)])

-- checks if n is a prime by checking if n is not composite 
isPrime :: Int -> Bool
isPrime n
    | n <= 0 = error "Makes no sense" 
    | n > 2 && even n = False 
    | otherwise = not (isComposite n)

-- filters out primes from a list of numbers 
getPrime :: [Int] -> [Int]
getPrime [] = []
getPrime (x:xs)
    | isPrime x = x : getPrime xs
    | otherwise = getPrime xs 

-- returns 3 biggest primes strictly smaller than n 
lastPrimes :: Int -> [Int]
lastPrimes n 
    | n <= 999999 = take 3 xs
    | otherwise = error "You've not tried to write primeFactors for big numbers yet"
    where xs = getPrime [(n-1), (n-2)..2]

-- returns Just xs where xs are unique 
primeFactors :: Int -> Maybe [Int]
primeFactors n 
    | n < 2 = Nothing
    | isPrime n = Nothing
    | otherwise = Just (unsafePrimeFactors n)

-- unsafe version of the function that does prime factorisation of n, returning just unique factors
unsafePrimeFactors :: Int -> [Int]
unsafePrimeFactors n 
    | n < 2 = []
    | isPrime n = [n]
    | otherwise = duplicateFree' ((xs) ++ unsafePrimeFactors (n `div` (head xs)))
    where xs = take 1 (filter (\x -> divides n x) [2..(n-1)])

{- 
Leave the error messages in place if you do not want to attempt the parts for the input size. You should remove the guards up to the point you want to attempt. For example, if you were confident of anything up to five digits, the function would look like:

primeFactors n
    | n <= 99999 = whatever_your_calculation_is
    | n <= 999999 = error "..."
    | otherwise = error "..."
-}

-- TEST SET FOR Q3
{-
Your functions should have the following behaviour:

lastPrimes 73 = [71,67,61]
lastPrimes 64 = [61,59,53]

DO NOT WORRY ABOUT THE ORDER OF THE LIST FOR lastPrimes

primeFactors 75 = Just [3,5]
primeFactors 64 = Just [2]
primeFactors 61 = Nothing

DO NOT WORRY ABOUT THE ORDER OF THE LIST FOR primeFactors
-}




-- QUESTION 4: RSA

-- returns a list of all integers less than n that are coprime with n 
totient' :: Int -> [Int] -> [Int] 
totient' n [] = []
totient' n (x:xs)  
    | gcd n x == 1 = x : totient' n xs
    | otherwise = totient' n xs

-- returns the number of integers that are smaller than n and coprime with n
eTotient :: Int -> Int
eTotient n
    | isPrime n = n - 1
    | otherwise = length (totient' n [1..(n-1)])

-- returns an encoded message usign the RSA encrypting algorithm 
encode :: Int -> Int -> Int -> Int -> Maybe Int
encode p q m e
    | isPrime p && isPrime q && ((gcd e (eTotient n)) == 1) = Just ((m^e) `mod` n)
    | otherwise = Nothing 
    where n = p * q

-- TEST SET FOR Q4
{-
Your functions should have the following behaviour:
eTotient 54 = 18
eTotient 73 = 72
encode 37 23 29 5 = Just 347
encode 99 18 108 45 = Nothing
encode 37 17 23 48 = Nothing
-}

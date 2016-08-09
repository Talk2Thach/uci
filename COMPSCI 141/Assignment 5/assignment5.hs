insert :: (Ord a) => [a] -> a -> [a]
insert [] x = [x]
insert (x:xs) y
  | y < x = (y:x:xs)
  | otherwise = (x:(insert xs y))



insertSort :: (Ord a) => [a] -> [a]
insertSort [] = []
insertSort (x:xs) = insert (insertSort xs) x



merge :: (Ord a) => [[a]] -> [a]
merge x = insertSort (concat x)



center :: [a] -> Int -> a -> [a]
center x i p
  | (length x) == i - 1 = (p:x)
  | (length x) < i - 1 = center (p:x ++ [p]) i p
  | otherwise = x



largest :: (Ord a) => [a] -> a
largest [] = error "empty list"
largest (x:xs) = foldl (\m n -> if m > n then m else n) x xs

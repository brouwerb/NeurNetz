ar = [3, 1, 6, 3, 6, 3, 2, 14, 353]

def rsort(arr):
    print(arr)
    if len(arr) > 1:
        devide = round(len(arr)/2)
        arr1 = rsort(arr[devide:])
        arr2 = rsort(arr[:devide])
        if arr1[0] <= arr2[0]:
            return arr1 + arr2
        else:
            return arr2 + arr1
    
    else:
        return arr
        
print(rsort(ar))
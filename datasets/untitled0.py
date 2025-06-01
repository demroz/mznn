class Solution:
    def search(self, nums, target):
        size = len(nums)
        leftindex = 0
        rightindex = size-1
        
        while leftindex < rightindex-1:
            midpoint = leftindex + int((rightindex-leftindex)/2)
            print(leftindex,rightindex,midpoint)
            if nums[midpoint] == target:
                return midpoint
            if nums[midpoint] > target:
                    rightindex = midpoint
            else:
                leftindex=midpoint


        return -1
 
sol = Solution()
print(sol.search(nums=[-1,0,2,4,6,8],target=3))
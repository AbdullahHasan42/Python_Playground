class water_and_glasses_problem():


    def __init__(self, N, K):
        self.N = N
        self.K = K
        self.glasses = list(range(N,0,-1))
        self.amount_poured = 0
        self.remaining_amount = K
        self.selected_glass = []
        self.i = 0


    def solution(self):
        while (self.amount_poured != self.K):
            if self.i == self.N:
                print("No Available Solution")
                return None
                break
            if (self.remaining_amount - self.glasses[self.i]) > 0 or (self.amount_poured + self.glasses[self.i]) <= self.K:
                self.remaining_amount = self.remaining_amount - self.glasses[self.i]
                self.amount_poured = self.amount_poured + self.glasses[self.i]
                self.selected_glass.append(glasses[self.i])
            self.i = self.i +1
        return self.selected_glass


# water_and_glasses_problem(5, 8).solution()
w = water_and_glasses_problem(5, 8)
w.solution()
def valueOption(s, x, t, r, b, u, d, nat = 'E', typ = 'C', prnt = True, exercisePeriods = []):
    """
    Calculates the fair option price of a simple option, inputs are as follows:
    s: The current stock price
    x: The strike price of the option
    t: The time in years until maturity of the option
    r: The current risk-free rate
    b: The number of branches to use in the option pricing
    v: The volatility of the underlying asset's price
    nat: 'A' for American (default), 'B' for Bermudan, 'E' for European 
    typ: 'C' for Call (default) or 'P' for Put
    prnt: True (default) to print variables to console, False to disable
    exercisePeriods: If option is Bermudan enter branches it is exercisable as a list.
    
    Returns:
    Option Value, Price Tree, Answer Tree
    """
    
    if min(s,x,t,b) <= 0:
        raise Exception('Inputs are Invalid: Use a positive value for s, x, t, b and v')
    
    if nat not in ['A', 'B', 'E']:
        raise Exception("Inputs are Invalid: Use 'A' for American Options, 'B' for Bermudan or 'E' for European")
    
    if typ not in ['C', 'P']:
        raise Exception("Inputs are Invalid: Use 'C' for Call Options or 'P' for Put Options")
        
    if type(prnt) != bool:
        raise Exception('Inputs are Invalid: Use True to print steps to console, False to Disable')
    
    exp = 2.718281828459045
    dt = t / b
    # u = exp ** (v * (dt ** 0.5))
    # d = 1/u
    p = (exp ** (r * (dt)) - d) / (u - d)
    q = (1-p)
        
    priceTree = [[s], [s * d, s * u]]
    for row in range(1, b):
        newRow = [priceTree[row][0] * d]
        for item in priceTree[row]:
            newRow.append(item * u) 
        priceTree.append(newRow)  
        
    IVTree =[]
    for row in priceTree:
        newRow = []
        for item in row:
            if typ == 'C':
                newRow.append(max(item-x,0))
            elif typ == 'P':
                newRow.append(max(x-item,0))         
        IVTree.append(newRow)
    
    answerTree = []
    for rowIndex in range(b):
        newRow = []
        for item in priceTree[rowIndex]:
            newRow.append(0)
        answerTree.append(newRow)
    answerTree.append(IVTree[b])

    if nat == 'A':
        exercisePeriods = list(range(b+1))
    elif nat == 'E':
        exercisePeriods = []

    for rowIndex in range(b - 1, -1, -1):    
        if rowIndex in exercisePeriods:
            exercisible = True
        else:
            exercisible = False
        for item in range(len(answerTree[rowIndex])):
            intrinsicValue = IVTree[rowIndex][item]
            discountedValue = exp ** (-r * dt) * (p * answerTree[rowIndex + 1][item + 1] + q * answerTree[rowIndex + 1][item])

            if exercisible == False or discountedValue >= intrinsicValue:
                answerTree[rowIndex][item] = discountedValue         
            else: 
                    answerTree[rowIndex][item] = intrinsicValue
    
    if prnt == True:
        print(f'The up-factor is {round(u, 4)} and the down-factor is {round(d, 4)}')
        print(f'\nThe probability of an upward price movement is {round(p, 4)}')
        print('\nThe stock price at each node is:')
        [print(['{0:.4f}'.format(item) for item in lst]) for lst in priceTree]
        print('\nThe option value at each node are:')
        [print(['{0:.4f}'.format(item) for item in lst]) for lst in answerTree]
        print(f'\nThe fair value of the {nat} {typ} Option is ${round(answerTree[0][0], 4)}')
    
    return answerTree[0][0], priceTree, answerTree

valueOption(30, 30, 5 / 365 , 0.07, 5, 1.15, 0.87, typ='C')
# valueOption(30, 30, 5 / 365 , 0.07, 1, 1.15, 0.87, typ='P')
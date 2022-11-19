import numpy as np

#function to calculate the chi2
def chi2(f, x, y, rho, a):
    return np.sum(((y - f(x, a))/rho)**2)

#beta

def beta(f, chi2, x, y, a, rho, h=np.sqrt(np.finfo(float).eps)):
    j = np.zeros(len(a))
    ak = np.zeros(len(a))
    for i in range(len(a)):
        ak[i] = np.sum((y - f(x, a))/rho**2 * (f(x, a+ h*a[i] * np.eye(len(a))[i]) - f(x, a - h*a[i] * np.eye(len(a))[i]))/(2*h*a[i]))
    return ak

# alpha

def alpha(f, chi2, x, y, a, rho, h=np.sqrt(np.finfo(float).eps)):
    ap = np.zeros((len(a), len(a)))
    for i in range(len(a)):
        for j in range(len(a)):
            ap[i, j] = np.sum(((f(x, a + h*a[i] * np.eye(len(a))[i]) - f(x, a - h*a[i] * np.eye(len(a))[i]))/(2*h*a[i]) * (f(x, a + h*a[i] * np.eye(len(a))[j]) - f(x, a - h*a[i] * np.eye(len(a))[j]))/(2*h*a[i])/rho**2))
    return ap

def ltep(f, chi2, x, y, a, rho, lam, h=np.sqrt(np.finfo(float).eps)):
    anew = a + (np.linalg.pinv(alpha(f, chi2, x, y, a, rho, h) + lam * np.diag(np.diag(alpha(f, chi2, x, y, a, rho, h)))) @ beta(f, chi2, x, y, a, rho, h))
    return anew


#calculate best fit parameters

def fit(f, x, y, a, rho=1, chi2=chi2, h=np.sqrt(np.finfo(float).eps)):
    lam = 1.0
    for i in range(1000):
        anew = ltep(f, chi2, x, y, a, rho, lam)


        

        if abs(chi2(f, x, y, rho, anew)) < abs(chi2(f, x, y, rho, a)):
            a = anew
            lam = lam/10

            
        else:
            lam = lam*10

            if lam > 1e10:
                break
    print("step", i, "chi2", chi2(f, x, y, rho, a))
    return a

if __name__ == "__main__":
    import matplotlib.pyplot as plt
    x = np.linspace(0, 1, 12)
    y = np.sin(2*np.pi*x) + np.random.normal(0, 0.2, 12)
    rho = 1
    a = np.ones(15)
    a = fit(f, x, y, a)

    print(a)
    print(chi2(f, x, y, rho, a))

    plt.plot(x, y, "o")
    plt.plot(np.linspace(min(x), max(x), 100), f(np.linspace(min(x), max(x), 100), a))
    plt.plot(np.linspace(min(x), max(x), 100), np.sin(np.pi*2*np.linspace(min(x), max(x), 100)))
    plt.show()
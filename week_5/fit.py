import numpy as np

#function to calculate the chi2
def chi2(x, y, rho, a):
    return np.sum(((y - f(x, a))/rho)**2)

#beta

def beta(f, chi2, x, y, a, rho, h=np.finfo(float).eps):
    j = np.zeros(len(a))
    ak = np.zeros(len(a))
    for i in range(len(a)):
        ak[i] = np.sum((y - f(x, a))/rho**2 * (f(x, a+ h*a[i] * np.eye(len(a))[i]) - f(x, a - h*a[i] * np.eye(len(a))[i]))/(2*h*a[i]))
    return ak

# alpha

def alpha(f, chi2, x, y, a, rho, h=np.finfo(float).eps):
    ap = np.zeros((len(a), len(a)))
    for i in range(len(a)):
        for j in range(len(a)):
            ap[i, j] = np.sum(((f(x, a + h*a[i] * np.eye(len(a))[i]) - f(x, a - h*a[i] * np.eye(len(a))[i]))/(2*h*a[i]) * (f(x, a + h*a[i] * np.eye(len(a))[j]) - f(x, a - h*a[i] * np.eye(len(a))[j]))/(2*h*a[i])/rho**2))
    return ap

def ltep(f, chi2, x, y, a, rho, lam, h=np.finfo(float).eps):
    anew = a + (np.linalg.pinv(alpha(f, chi2, x, y, a, rho, h) + lam * np.diag(np.diag(alpha(f, chi2, x, y, a, rho, h)))) @ beta(f, chi2, x, y, a, rho, h))
    return anew


#calculate best fit parameters

def fit(f, x, y, a, rho, lam=1.0, h=np.finfo(float).eps):

    for i in range(1000):
        anew = ltep(f, chi2, x, y, a, rho, lam)
        print(f"step {i}")
        print(chi2(x, y, rho, a), chi2(x, y, rho, anew))
        

        if abs(chi2(x, y, rho, anew)) < abs(chi2(x, y, rho, a)):
            a = anew
            lam = lam/10
            print(lam)
            
        else:
            lam = lam*10
            print(lam)
            if lam > 1e10:
                break
        
    return a

def f(x, a):
    return a[0] + a[1]*x + a[2]*x**2 + a[3]*x**3 + a[4]*x**4 + a[5]*x**5

if __name__ == "__main__":
    import matplotlib.pyplot as plt
    x = np.linspace(0, 1, 10)
    y = np.sin(2*np.pi*x) + np.random.normal(0, 0.2, 10)
    rho = np.ones(10)
    a = np.array([1, 1, 1, 1, 1, 1])
    a = fit(f, x, y, a, rho)

    print(a)
    print(chi2(x, y, rho, a))

    plt.plot(x, y, "o")
    plt.plot(x, f(x, a))
    plt.show()
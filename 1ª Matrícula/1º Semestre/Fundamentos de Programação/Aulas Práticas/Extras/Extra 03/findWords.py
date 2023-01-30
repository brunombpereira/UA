
# This function reads a file and returns a list with every line stripped.
def load(fname):
    with open(fname) as f:
        lst = []
        for line in f:
            word = line.strip()
            lst.append(word)
    return lst


"""
Complete a função filterPattern(lst, pattern) para extrair duma lista de strings
as strings que têm o padrão dado.
Sugestão: invoque a função matchesPattern (ver abaixo) para testar cada palavra.
"""
def filterPattern(lst, pattern):
    # Complete ...


"""
Complete a função matchesPattern(s, pattern) para devolver
True se s corresponder ao padrão fornecido e False, no caso contrário.
Uma string s corresponde ao padrão se e só se tiver os mesmos carateres
que o padrão nas mesmas posições, exceto onde o padrão tem ?.
Nas posições dos ?, não importa que carateres estão na string s.
A correspondência não deve fazer distinção entre maiúsculas e minúsculas.

Complete matchesPattern(s, pattern) to return
True if s matches the given pattern and return False, otherwise.
A string s matches the pattern if and only if it has the same characters
as the pattern in the same positions, except where the pattern has ?.
Wherever the pattern has ?, it doesn't matter which characters are in s.
Matching should be case-insensitive.
"""
def matchesPattern(s, pattern):
    # Complete ...


def main():
    # Uncomment these lines to test the matchesPattern function:
    #assert matchesPattern("secret", "s?c??t") == True
    #assert matchesPattern("secreta", "s?c??t") == False
    #assert matchesPattern("socket", "s?c??t") == True
    #assert matchesPattern("soccer", "s?c??t") == False
    #assert matchesPattern("SEcrEt", "?ecr?t") == True, "should be case-insensitive"
    #assert matchesPattern("SEcrET", "?ecr?t") == True, "should be case-insensitive"
    #assert matchesPattern("SecrEt", "?ECR?T") == True, "should be case-insensitive"

    words = load("wordlist.txt")

    lst = filterPattern(words, "s?c??t")
    print(lst)

    assert isinstance(lst, list),  "result lst should be a list"
    assert "secret" in lst,  "result should contain 'secret'"

    # Solution to "?YS???Y"
    lst = filterPattern(words, "?ys???y")
    print(lst)


# Call main function:
if __name__ == "__main__":
    main()


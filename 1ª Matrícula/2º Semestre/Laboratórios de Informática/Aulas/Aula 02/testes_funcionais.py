import pytest


def test_sum():
    assert soma(2, 3) == 5
    assert soma(0, 0) == 0
    assert soma(-2, 5) == 3

def test_subtract():
    assert subtracao(5, 2) == 3
    assert subtracao(0, 0) == 0
    assert subtracao(-2, -5) == 3

def test_multiply():
    assert multiplicacao(2, 3) == 6
    assert multiplicacao(0, 0) == 0
    assert multiplicacao(-2, 5) == -10

def test_divide():
    assert divisao(6, 3) == 2
    assert divisao(6, -3) == -2
    assert divisao(0, 5) == 0
    with pytest.raises(ZeroDivisionError):
        divisao(5, 0)

def test_invalid_arguments():
    with pytest.raises(TypeError):
        soma(2, "3")
    with pytest.raises(TypeError):
        subtracao("5", 2)
    with pytest.raises(TypeError):
        multiplicacao(2, "3")
    with pytest.raises(TypeError):
        divisao("6", 3)

def test_missing_arguments():
    with pytest.raises(TypeError):
        soma(2)
    with pytest.raises(TypeError):
        subtracao()
    with pytest.raises(TypeError):
        multiplicacao()
    with pytest.raises(TypeError):
        divisao(6)


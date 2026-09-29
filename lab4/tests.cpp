#define main snake_game_main
#include "../game.cpp"
#undef main

#include <cassert>
#include <iostream>

using namespace std;

void initializeSnake(Snake &snake)
{
    node *n1 = snake.head;
    node *n2 = n1->next;
    node *n3 = n2->next;

    n1->mi = 1;
    n1->mj = 1;

    n2->mi = 1;
    n2->mj = 2;

    n3->mi = 1;
    n3->mj = 3;
}

class FakeInput : public InputProvider
{
public:
    char key;

    FakeInput(char k)
    {
        key = k;
    }

    char get() override
    {
        return key;
    }
};

void test_onSnake()
{
    Snake snake;
    initializeSnake(snake);

    assert(snake.onSnake(1, 1));
    assert(snake.onSnake(1, 2));
    assert(snake.onSnake(1, 3));
    assert(!snake.onSnake(10, 10));
}

void test_hitSnake()
{
    Snake snake;
    initializeSnake(snake);

    assert(snake.hitSnake(1, 2));
    assert(snake.hitSnake(1, 3));
    assert(!snake.hitSnake(10, 10));
}

void test_changeIndex()
{
    Snake snake;
    initializeSnake(snake);

    snake.m1 = 2;
    snake.m2 = 2;

    snake.changeIndex();

    assert(snake.head->mi == 2);
    assert(snake.head->mj == 2);

    assert(snake.head->next->mi == 1);
    assert(snake.head->next->mj == 1);

    assert(snake.head->next->next->mi == 1);
    assert(snake.head->next->next->mj == 2);
}

void test_w_key_changes_direction()
{
    FakeInput fakeInput('w');
    GameBoard game(&fakeInput);

    game.handleInput();

    assert(game.snake.dx == -1);
    assert(game.snake.dy == 0);
    assert(game.snake.hch == '^');
}

int main()
{
    test_onSnake();
    test_hitSnake();
    test_changeIndex();
    test_w_key_changes_direction();

    cout << "All tests passed\n";

    return 0;
}

#include "raylib.h"
#include <stdbool.h>

const int screenWid = 300;
const int screenHig = 600;
const int cellSize = 30;
const int cols = 10;
const int rows = 20;

typedef struct Board {
    int grid[20][10];
} Board;

void DrawBoard(Board* board) {
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (board->grid[r][c] != 0) {
                DrawRectangle(c * cellSize, r * cellSize, cellSize - 2, cellSize - 2, GRAY);
            }
            DrawRectangleLines(c * cellSize, r * cellSize, cellSize, cellSize, LIGHTGRAY);
        }
    }
}

bool CanMove(Board* board, int x, int y) {
    if (x < 0 || x >= cols || y >= rows) return false;
    if (y < 0) return true;
    return board->grid[y][x] == 0;
}

void LockPiece(Board* board, int x, int y) {
    if (y >= 0) board->grid[y][x] = 1;
}

typedef struct Piece {
    int x;
    int y;
    Color color;
} Piece;

void DrawPiece(Piece* piece) {
    DrawRectangle(piece->x * cellSize, piece->y * cellSize, cellSize - 2, cellSize - 2, piece->color);
}

bool MovePiece(Piece* piece, int dx, int dy, Board* board) {
    if (CanMove(board, piece->x + dx, piece->y + dy)) {
        piece->x += dx;
        piece->y += dy;
        return true;
    }
    return false;
}

void ResetPiece(Piece* piece) {
    piece->x = 4;
    piece->y = 0;
}

int main() {
    InitWindow(screenWid, screenHig, "ANU Tetris");
    SetTargetFPS(60);

    Board board = { 0 };
    Piece piece = { 4, 0, BLUE };
    float timer = 0;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_LEFT))  MovePiece(&piece, -1, 0, &board);
        if (IsKeyPressed(KEY_RIGHT)) MovePiece(&piece, 1, 0, &board);
        if (IsKeyPressed(KEY_DOWN))  MovePiece(&piece, 0, 1, &board);

        timer += GetFrameTime();
        if (timer >= 0.5f) {
            if (!MovePiece(&piece, 0, 1, &board)) {
                LockPiece(&board, piece.x, piece.y);
                ResetPiece(&piece);
            }
            timer = 0;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawBoard(&board);
        DrawPiece(&piece);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
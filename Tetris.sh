if [ ! -d "executable_linux" ]; then
    wget https://github.com/adam-choragwicki/Tetris_Game_Qt_Cplusplus/releases/latest/download/executable_linux.zip
    unzip executable_linux.zip && rm executable_linux.zip
    chmod +x executable_linux/Tetris.sh executable_linux/Tetris
fi

./executable_linux/Tetris

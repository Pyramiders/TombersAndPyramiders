#pragma once

class Randomize {
    private:
		const static int MAX_INT;
    
    public:
		static void SetSeed (int seed);

		static int Random (int min = 0, int max = MAX_INT);

		static float RandomFloat (int min = 0, int max = MAX_INT);
};

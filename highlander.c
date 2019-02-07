void fill (char*** map, int width, int height, char item) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < height - 1; j++) {
			(*map)[i][j] = item;
		}
		(*map)[i][height - 1] = '\n';
	}
}

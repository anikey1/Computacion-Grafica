//Anikey Andrea Gómez Guzman  319323290
//Fecha de entrega: 23 de febrero, 2026

#include <iostream>

//#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Shaders
#include "Shader.h"

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 800, HEIGHT = 600;

int main() {
	glfwInit();

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Dibujo de Primitivas en 2D", NULL, NULL);
	glfwSetFramebufferSizeCallback(window, resize);

	// Verificación de errores de creación ventana
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	// Verificación de errores de inicialización de GLEW
	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Información de OpenGL
	std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	Shader ourShader("Shader/core.vs", "Shader/core.frag");

	// =========================
	// VÉRTICES (pos + color)
	// =========================
	float vertices[] = {
		// x, y, z, r, g, b

		// --- Cabeza (pentágono) ---
		0.00f, 0.78f, 0.0f, 0,0,0, // 0
		-0.07f, 0.73f, 0.0f, 0,0,0, // 1
		-0.05f, 0.66f, 0.0f, 0,0,0, // 2
		0.05f, 0.66f, 0.0f, 0,0,0, // 3
		0.07f, 0.73f, 0.0f, 0,0,0, // 4

		// --- Cuello / unión ---
		-0.12f, 0.60f, 0.0f, 0,0,0, // 5
		0.12f, 0.60f, 0.0f, 0,0,0, // 6
		-0.08f, 0.52f, 0.0f, 0,0,0, // 7
		0.08f, 0.52f, 0.0f, 0,0,0, // 8

		// --- Caparazón exterior (hexágono grande) ---
		0.00f, 0.52f, 0.0f, 0,0,0, // 9
		-0.22f, 0.40f, 0.0f, 0,0,0, // 10
		-0.22f, 0.12f, 0.0f, 0,0,0, // 11
		0.00f, -0.02f, 0.0f, 0,0,0, // 12
		0.22f, 0.12f, 0.0f, 0,0,0, // 13
		0.22f, 0.40f, 0.0f, 0,0,0, // 14

		// --- Líneas internas ---
		-0.14f, 0.44f, 0.0f, 0,0,0, // 15
		0.14f, 0.44f, 0.0f, 0,0,0, // 16
		-0.18f, 0.26f, 0.0f, 0,0,0, // 17
		0.18f, 0.26f, 0.0f, 0,0,0, // 18
		-0.14f, 0.08f, 0.0f, 0,0,0, // 19
		0.14f, 0.08f, 0.0f, 0,0,0, // 20

		// --- Aletas superiores (izq / der) ---
		-0.26f, 0.48f, 0.0f, 0,0,0, // 21
		-0.48f, 0.56f, 0.0f, 0,0,0, // 22
		-0.56f, 0.40f, 0.0f, 0,0,0, // 23
		-0.42f, 0.32f, 0.0f, 0,0,0, // 24

		0.26f, 0.48f, 0.0f, 0,0,0, // 25
		0.48f, 0.56f, 0.0f, 0,0,0, // 26
		0.56f, 0.40f, 0.0f, 0,0,0, // 27
		0.42f, 0.32f, 0.0f, 0,0,0, // 28

		// --- Patas inferiores (izq / der) ---
		-0.16f, -0.02f, 0.0f, 0,0,0, // 29
		-0.28f, -0.16f, 0.0f, 0,0,0, // 30
		-0.20f, -0.34f, 0.0f, 0,0,0, // 31
		-0.06f, -0.30f, 0.0f, 0,0,0, // 32

		0.16f, -0.02f, 0.0f, 0,0,0, // 33
		0.28f, -0.16f, 0.0f, 0,0,0, // 34
		0.20f, -0.34f, 0.0f, 0,0,0, // 35
		0.06f, -0.30f, 0.0f, 0,0,0, // 36

		// --- Cola (rombo) ---
		-0.04f, -0.06f, 0.0f, 0,0,0, // 37
		0.04f, -0.06f, 0.0f, 0,0,0, // 38
		0.00f, -0.12f, 0.0f, 0,0,0, // 39
	};

	// =========================
	// ÍNDICES PARA GL_LINES
	// (pares: a,b) conectan un segmento
	// =========================
	unsigned int indices[] = {
		// Cabeza
		0,1, 1,2, 2,3, 3,4, 4,0,

		// Cuello
		5,6, 5,7, 6,8, 7,8,
		7,9, 8,9,

		// Caparazón exterior
		9,10, 10,11, 11,12, 12,13, 13,14, 14,9,

		// Internas horizontales
		15,16,
		17,18,
		19,20,

		// Internas diagonales/verticales
		9,15, 15,10, 9,16, 16,14,
		15,17, 17,11, 16,18, 18,13,
		17,19, 19,12, 18,20, 20,12,

		// Aleta izquierda (contorno)
		21,22, 22,23, 23,24, 24,10, 21,10,
		// Detalle interno aleta izq
		22,10, 24,21,

		// Aleta derecha (contorno)
		25,26, 26,27, 27,28, 28,14, 25,14,
		// Detalle interno aleta der
		26,14, 28,25,

		// Pata inferior izquierda
		29,11, 29,30, 30,31, 31,32, 32,12, 29,12,

		// Pata inferior derecha
		33,13, 33,34, 34,35, 35,36, 36,12, 33,12,

		// Cola (rombo)
		37,38, 38,39, 39,37,
	};

	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Enlazar VAO
	glBindVertexArray(VAO);

	// VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Posición
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		// Fondo gris claro como la imagen
		glClearColor(0.85f, 0.85f, 0.85f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ourShader.Use();
		glBindVertexArray(VAO);

		// Dibujar líneas (toda la figura)
		glDrawElements(GL_LINES, (GLsizei)(sizeof(indices) / sizeof(indices[0])), GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return EXIT_SUCCESS;
}

void resize(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

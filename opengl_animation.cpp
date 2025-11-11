#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include "aircraft.cpp"
#include <chrono>

// =====================================================
// Aircraft Flight Simulator - Optimized OpenGL Version
// Author: VacationAir
// Description: Real-time aircraft simulation with optimized graphics
// =====================================================

// Constants
const double METERS_TO_PIXELS = 0.1;    // Scale: 0.1 pixels per meter
const double TIME_STEP = 0.05;          // Physics time step (50ms)
const int TRAJECTORY_MAX_POINTS = 500;  // Limit trajectory points for performance

// Global variables
struct Point { double x, y; };
std::vector<Point> trajectory;
Aircraft aircraft(600, 0.75, 0, 46.3, 610, 4.1, 82000, 14.9);
double camera_offset = 0;
int window_width = 1200;
int window_height = 800;
auto simulation_start = std::chrono::steady_clock::now();
double elapsed_time_seconds = 0.0;
bool paused = false;

// =====================================================
// Utility Functions
// =====================================================

/**
 * Converts meters to pixel coordinates for rendering
 */
double metersToPixels(double meters) {
    return meters * METERS_TO_PIXELS;
}

/**
 * Formats double to string with specified precision
 */
std::string formatDouble(double value, int precision = 0) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(precision) << value;
    return ss.str();
}

/**
 * Draws text on screen using GLUT bitmap fonts
 */
void drawText(float x, float y, const std::string& text, void* font = GLUT_BITMAP_HELVETICA_12) {
    glRasterPos2f(x, y);
    for (char c : text) {
        glutBitmapCharacter(font, c);
    }
}
/**
 * Updates the timer
 */
void updateSimulationTime() {
    if (!paused) {
        auto now = std::chrono::steady_clock::now();
        elapsed_time_seconds = std::chrono::duration<double>(now - simulation_start).count();
    }
}

// =====================================================
// Drawing Functions
// =====================================================

/**
 * Draws a detailed aircraft model with proper scaling
 */
void drawAircraft(double x, double y, double pitch_angle_deg) {
    glPushMatrix();
    glTranslated(x, y, 0);
    glRotated(pitch_angle_deg, 0, 0, 1);
    
    // Aircraft scale factor (larger for better visibility)
    const double SCALE = 2.5;
    glScaled(SCALE, SCALE, 1.0);

    // Fuselage (main body)
    glColor3f(0.9f, 0.1f, 0.1f); // Red
    glBegin(GL_TRIANGLES);
    glVertex2f(2.5f, 0.0f);      // Nose
    glVertex2f(-1.8f, 0.7f);     // Top rear
    glVertex2f(-1.8f, -0.7f);    // Bottom rear
    glEnd();

    // Main wings
    glColor3f(0.2f, 0.2f, 0.6f); // Dark blue
    glBegin(GL_QUADS);
    // Right wing
    glVertex2f(-0.3f, 0.1f);
    glVertex2f(-0.3f, 2.0f);
    glVertex2f(0.3f, 2.0f);
    glVertex2f(0.3f, 0.1f);
    // Left wing
    glVertex2f(-0.3f, -0.1f);
    glVertex2f(-0.3f, -2.0f);
    glVertex2f(0.3f, -2.0f);
    glVertex2f(0.3f, -0.1f);
    glEnd();

    // Tail wings
    glColor3f(0.3f, 0.3f, 0.7f);
    glBegin(GL_QUADS);
    // Horizontal stabilizer
    glVertex2f(-2.0f, 0.1f);
    glVertex2f(-2.0f, 0.8f);
    glVertex2f(-1.2f, 0.8f);
    glVertex2f(-1.2f, 0.1f);
    
    glVertex2f(-2.0f, -0.1f);
    glVertex2f(-2.0f, -0.8f);
    glVertex2f(-1.2f, -0.8f);
    glVertex2f(-1.2f, -0.1f);
    glEnd();

    // Vertical stabilizer
    glBegin(GL_TRIANGLES);
    glVertex2f(-1.8f, 0.0f);
    glVertex2f(-2.5f, 0.0f);
    glVertex2f(-1.8f, 1.2f);
    glEnd();

    // Cockpit
    glColor3f(0.8f, 0.9f, 1.0f); // Light blue
    glBegin(GL_QUADS);
    glVertex2f(1.0f, 0.2f);
    glVertex2f(1.0f, -0.2f);
    glVertex2f(0.3f, -0.2f);
    glVertex2f(0.3f, 0.2f);
    glEnd();

    // Engine nacelle
    glColor3f(0.3f, 0.3f, 0.3f); // Gray
    glBegin(GL_QUADS);
    glVertex2f(2.2f, 0.15f);
    glVertex2f(2.2f, -0.15f);
    glVertex2f(1.5f, -0.15f);
    glVertex2f(1.5f, 0.15f);
    glEnd();

    glPopMatrix();
}

/**
 * Draws the environment including sky, ground
 */
void drawEnvironment() {
    // Sky gradient
    glBegin(GL_QUADS);
    glColor3f(0.53f, 0.81f, 0.98f); // Light blue top
    glVertex2f(-200, 400);
    glVertex2f(800, 400);
    glColor3f(0.68f, 0.85f, 0.90f); // Lighter blue bottom
    glVertex2f(800, 0);
    glVertex2f(-200, 0);
    glEnd();

    // Ground
    glColor3f(0.1f, 0.5f, 0.1f); // Dark green
    glBegin(GL_QUADS);
    glVertex2f(-200, 0);
    glVertex2f(800, 0);
    glVertex2f(800, -100);
    glVertex2f(-200, -100);
    glEnd();

    // Horizon line
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex2f(-200, metersToPixels(500));
    glVertex2f(800, metersToPixels(500));
    glEnd();
}

/**
 * Draws the aircraft's flight path
 */
void drawTrajectory() {
    if (trajectory.size() < 2) return;
    
    glColor4f(1.0f, 0.8f, 0.2f, 0.7f); // Semi-transparent yellow
    glEnable(GL_LINE_SMOOTH);
    glBegin(GL_LINE_STRIP);
    for (const auto& point : trajectory) {
        glVertex2f(point.x, point.y);
    }
    glEnd();
    glDisable(GL_LINE_SMOOTH);
}

/**
 * Draws the Heads-Up Display with flight information on the right side
 */
void drawHUD() {
    // Calculate HUD dimensions based on text content
    const int hud_width = 220;
    const int hud_height = 180;
    const int hud_x = window_width - hud_width - 20; // 20px from right edge
    const int hud_y = window_height - hud_height - 20; // 20px from top
    
    // HUD background (semi-transparent black)
    glColor4f(0.0f, 0.0f, 0.0f, 0.8f);
    glBegin(GL_QUADS);
    glVertex2f(hud_x, hud_y);
    glVertex2f(hud_x + hud_width, hud_y);
    glVertex2f(hud_x + hud_width, hud_y + hud_height);
    glVertex2f(hud_x, hud_y + hud_height);
    glEnd();

    // HUD border
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(hud_x, hud_y);
    glVertex2f(hud_x + hud_width, hud_y);
    glVertex2f(hud_x + hud_width, hud_y + hud_height);
    glVertex2f(hud_x, hud_y + hud_height);
    glEnd();

    // Flight data display - Green HUD text
    glColor3f(0.0f, 1.0f, 0.0f);
    
    int text_x = hud_x + 10;
    int text_y = hud_y + hud_height - 25;
    int line_height = 20;
    
    // Title
    drawText(text_x, text_y, "AIRCRAFT STATUS", GLUT_BITMAP_HELVETICA_18);
    text_y -= line_height + 5;
    
    // Data rows with proper spacing
    drawText(text_x, text_y, "Altitude: " + formatDouble(aircraft.getAltitude(), 0) + " m");
    text_y -= line_height;
    
    drawText(text_x, text_y, "Speed: " + formatDouble(aircraft.getSpeed(), 1) + " m/s");
    text_y -= line_height;
    
    drawText(text_x, text_y, "Position: " + formatDouble(aircraft.getPosition(), 0) + " m");
    text_y -= line_height;
    
    drawText(text_x, text_y, "Vert Speed: " + formatDouble(aircraft.getVs(), 1) + " m/s");
    text_y -= line_height;
    
    drawText(text_x, text_y, "Pitch: " + formatDouble(aircraft.getAngleThetaDegree(), 1) + " deg");
    text_y -= line_height;
    
    drawText(text_x, text_y, "Acceleration: " + formatDouble(aircraft.getAcceleration(), 2) + " m/s²");
    text_y -= line_height;
    
    drawText(text_x, text_y, "Time: " + formatDouble(elapsed_time_seconds, 1) + " s");
}

// =====================================================
// Core Simulation Functions
// =====================================================

/**
 * Main display callback function
 */
void display() {
    updateSimulationTime();
    glClear(GL_COLOR_BUFFER_BIT);

    // Update aircraft physics
    aircraft.update(TIME_STEP);

    // Calculate current position in pixel coordinates
    double aircraft_x = metersToPixels(aircraft.getPosition());
    double aircraft_y = metersToPixels(aircraft.getAltitude());

    // Add current position to trajectory
    trajectory.push_back({aircraft_x, aircraft_y});
    
    // Limit trajectory size for performance
    if (trajectory.size() > TRAJECTORY_MAX_POINTS) {
        trajectory.erase(trajectory.begin());
    }

    // Update camera to follow aircraft (centered with offset)
    camera_offset = aircraft_x - (window_width * 0.4); // Keep aircraft at 40% from left

    // Switch to world coordinates for scene rendering
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-200 + camera_offset, 600 + camera_offset, 0, 400);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Draw all scene elements
    drawEnvironment();
    drawTrajectory();
    drawAircraft(aircraft_x, aircraft_y, aircraft.getAngleThetaDegree());

    // Switch to screen coordinates for UI elements
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, window_width, 0, window_height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    drawHUD();

    glutSwapBuffers();
}

/**
 * Window resize handler
 */
void reshape(int width, int height) {
    window_width = width;
    window_height = height;
    glViewport(0, 0, width, height);
}

/**
 * Timer function for continuous animation
 */
void timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0); // ~60 FPS
}

/**
 * Keyboard input handler
 */
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27: // ESC key
            std::cout << "Simulation terminated by user." << std::endl;
            exit(0);
            break;
        case 'r':
        case 'R':
            // Reset trajectory
            trajectory.clear();
            std::cout << "Trajectory cleared." << std::endl;
            break;
        case ' ':
            // Space bar to toggle pause
            static bool paused = false;
            paused = !paused;
            if (paused) {
                std::cout << "Simulation paused." << std::endl;
                // In a real implementation, you'd stop the timer here
            } else {
                std::cout << "Simulation resumed." << std::endl;
            }
            break;
    }
}

/**
 * Initialize OpenGL settings
 */
void initOpenGL() {
    glClearColor(0.6f, 0.8f, 1.0f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
}

/**
 * Main simulation entry point
 */
void runOpenGLSimulation(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(window_width, window_height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Aircraft Flight Simulator - Enhanced OpenGL Viewer");

    // Set up callbacks and start simulation
    initOpenGL();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, timer, 0);
    
    std::cout << "=== Aircraft Flight Simulator ===" << std::endl;
    std::cout << "Controls:" << std::endl;
    std::cout << "  ESC   - Exit simulation" << std::endl;
    std::cout << "  R     - Reset trajectory" << std::endl;
    std::cout << "  SPACE - Pause simulation" << std::endl;
    std::cout << "Scale: 1 pixel = " << (1.0/METERS_TO_PIXELS) << " meters" << std::endl;
    std::cout << "Starting simulation..." << std::endl;

    glutMainLoop();
}
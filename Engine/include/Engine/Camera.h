#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Engine {
    class Camera {
    public:
        enum class Direction {
            FORWARD,
            BACKWARD,
            RIGHT,
            LEFT
        };

        Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f));

        glm::mat4 getViewMatrix() const;

        void processKeyboard(Direction direction, float deltatime);

        void processMouseMovement(float xOffset, float yOffset);

        void processMouseScroll(float yOffset);

        float getZoom() const;

    private:
        //default values
        float m_yaw = -90.0f;
        float m_pitch = 0.0f;
        float m_speed = 7.5f;
        float m_sens = 0.1f;
        float m_zoom = 45.0f;

        glm::vec3 m_position;
        glm::vec3 m_front;
        glm::vec3 m_up;
        glm::vec3 m_right;
        glm::vec3 m_worldUp;

        void updateVectors();
    };
}
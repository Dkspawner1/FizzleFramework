#include <Graphics/GraphicsDeviceManager.h>

GraphicsDeviceManager::GraphicsDeviceManager(const std::string &title, int width, int height) : m_isFullScreen(false) {
    m_window = std::make_unique<Window>(title, width, height);
    m_renderer = std::make_unique<Renderer>(m_window.get());
}

GraphicsDeviceManager::~GraphicsDeviceManager() = default;

void GraphicsDeviceManager::Initialize() {
    m_window->Initialize();
    m_renderer->Initialize();
}

void GraphicsDeviceManager::BeginDraw() {
    m_renderer->Clear();
}

void GraphicsDeviceManager::EndDraw() {
    m_renderer->Present();
}

bool GraphicsDeviceManager::IsFullScreen() const {
    return m_isFullScreen;
}

void GraphicsDeviceManager::ToggleFullScreen() {
    m_isFullScreen = !m_isFullScreen;
    m_window->SetFullScreen(m_isFullScreen);
}

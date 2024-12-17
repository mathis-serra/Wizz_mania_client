#include "../hpp_files/UIManager.h"

UIManager::UIManager(float windowWidth, float windowHeight)
    : windowWidth(windowWidth),
      maxInputWidth(windowWidth * 0.6f),
      maxInputHeight(windowHeight - 100.0f),
      lineSpacing(20.0f),
      currentHeight(21.0f),
      scrollOffset(0.0f),
      sendButton(sf::Vector2f(100, 50), sf::Vector2f(windowWidth - 127, windowHeight - 70), "Envoyer", font),
      wizzButton(sf::Vector2f(30, 50), sf::Vector2f(windowWidth - 163, windowHeight - 70), ":D", font) {
    inputBox.setSize(sf::Vector2f(windowWidth - 160, 50));
    inputBox.setFillColor(sf::Color(243, 238, 217));
    inputBox.setPosition(0, windowHeight - 50);

    inputScrollbar.setFillColor(sf::Color(150, 150, 150));
    inputScrollbar.setSize(sf::Vector2f(5, maxInputHeight));
    inputScrollbar.setPosition(inputBox.getSize().x - 5, 0);
}

void UIManager::loadFont(const std::string& fontPath) {
    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Erreur : Impossible de charger la police " << fontPath << " !" << std::endl;
    }
}

void UIManager::addMessage(const std::string& message, MessageType type) {
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);

    // Word wrapping logic
    std::istringstream words(message);
    std::string word;
    std::string wrappedMessage;
    float lineWidth = 0.0f;
    float maxLineWidth = 0.0f;  // Track the maximum line width

    while (words >> word) {
        sf::Text tempText = text;
        tempText.setString(word + " ");
        float wordWidth = tempText.getLocalBounds().width;

        // If the word doesn't fit in the current line, start a new line
        if (lineWidth + wordWidth > maxInputWidth - 20) {
            wrappedMessage += "\n" + word + " ";
            lineWidth = wordWidth;  // Reset line width to the current word's width
        } else {
            wrappedMessage += word + " ";
            lineWidth += wordWidth;
        }

        maxLineWidth = std::max(maxLineWidth, lineWidth);  // Keep track of the longest line
    }

    text.setString(wrappedMessage);

    // Calculate bubble width dynamically based on the longest line
    sf::FloatRect textBounds = text.getLocalBounds();
    float bubbleWidth = maxLineWidth + 20;  // Add some padding
    float bubbleHeight = textBounds.height + (text.getLineSpacing() * (std::count(wrappedMessage.begin(), wrappedMessage.end(), '\n') + 1)) + 20;

    // Create the message bubble
    sf::RectangleShape bubble;
    bubble.setSize(sf::Vector2f(bubbleWidth, bubbleHeight));
    bubble.setFillColor(type == MessageType::Received ? sf::Color(87, 66, 64) : sf::Color(243, 238, 217));
    bubble.setOutlineThickness(1);
    bubble.setOutlineColor(sf::Color(27, 105, 95));

    // Set the position based on whether it's a sent or received message
    float xOffset = (type == MessageType::Received) ? 50.0f : (windowWidth - bubbleWidth - 50.0f);
    float yOffset = currentHeight;

    text.setPosition(xOffset + 10, yOffset + 10);  // Position text with padding
    bubble.setPosition(xOffset, yOffset);  // Position the bubble

    // Update currentHeight for the next message
    currentHeight += bubbleHeight + lineSpacing;

    // Update scroll offset if necessary
    float maxScrollOffset = std::max(0.0f, currentHeight - maxInputHeight);
    if (currentHeight > maxInputHeight) {
        scrollOffset = maxScrollOffset;
    }

    // Store the message and bubble
    messageBubbles.push_back({text, bubble});
    updateScroll();
}

void UIManager::handleTextEntered(sf::Uint32 unicode, std::string& userInput) {
    if (unicode == '\b') {
        if (!userInput.empty()) {
            userInput.pop_back();
        }
    } else if (unicode < 128) {
        userInput += static_cast<char>(unicode);
    }

    inputText.setString(userInput);
}

void UIManager::handleScroll(float delta) {
    float scrollAmount = 30.0f;
    float maxScrollOffset = std::max(0.0f, currentHeight - maxInputHeight);

    scrollOffset = std::clamp(scrollOffset - delta * scrollAmount, 0.0f, maxScrollOffset);
}

void UIManager::updateScroll() {
    float totalHeight = currentHeight;
    float visibleHeight = maxInputHeight;

    float scrollbarHeight = (visibleHeight / totalHeight) * maxInputHeight;
    scrollbarHeight = std::min(scrollbarHeight, maxInputHeight);

    inputScrollbar.setSize(sf::Vector2f(5, scrollbarHeight));

    float maxScrollOffset = std::max(0.0f, totalHeight - visibleHeight);
    if (maxScrollOffset > 0) {
        float scrollbarPosition = (scrollOffset / maxScrollOffset) * (maxInputHeight - scrollbarHeight);
        inputScrollbar.setPosition(inputBox.getSize().x - 5, scrollbarPosition);
    } else {
        inputScrollbar.setPosition(inputBox.getSize().x - 5, 0);
    }
}

void UIManager::renderUI(sf::RenderWindow& window, const std::string& userInput) {

    sf::RectangleShape marginBackground;
    marginBackground.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    marginBackground.setFillColor(sf::Color(243, 238, 217));
    window.draw(marginBackground);

    sf::RectangleShape contentBackground;
    float marginSize = 20.0f;
    contentBackground.setSize(sf::Vector2f(window.getSize().x - 2 * marginSize, window.getSize().y - 2 * marginSize));
    contentBackground.setPosition(marginSize, marginSize);
    contentBackground.setFillColor(sf::Color(27, 105, 95));
    window.draw(contentBackground);

    sf::RectangleShape lowerBackground;
    lowerBackground.setSize(sf::Vector2f(760, 50));
    lowerBackground.setFillColor(sf::Color(27, 105, 95));
    lowerBackground.setPosition(20, inputBox.getPosition().y);

    sf::RectangleShape lowerBar;
    lowerBar.setSize(sf::Vector2f(800, 20));
    lowerBar.setFillColor(sf::Color(243, 238, 217));
    lowerBar.setPosition(0, inputBox.getPosition().y + 50);

    sf::RectangleShape upperBar;
    upperBar.setSize(sf::Vector2f(800, 20));
    upperBar.setFillColor(sf::Color(243, 238, 217));
    upperBar.setPosition(0, 0);

    inputBox.setPosition(marginSize + 10, window.getSize().y - marginSize - 50);
    inputBox.setSize(sf::Vector2f(window.getSize().x - 2 * marginSize - 160, 50));

    inputText.setFont(font);
    inputText.setCharacterSize(24);
    inputText.setFillColor(sf::Color::Black);
    inputText.setString(userInput);
    inputText.setPosition(inputBox.getPosition().x + 10, inputBox.getPosition().y + 10);

    for (const auto& bubble : messageBubbles) {
        sf::RectangleShape adjustedBubble = bubble.bubble;
        sf::Text adjustedText = bubble.text;

        sf::Vector2f position = adjustedBubble.getPosition();
        position.y -= scrollOffset;
        position.x += marginSize;
        adjustedBubble.setPosition(position);

        sf::Vector2f textPosition = adjustedText.getPosition();
        textPosition.y -= scrollOffset;
        textPosition.x += marginSize;
        adjustedText.setPosition(textPosition);

        if (position.y + adjustedBubble.getSize().y > marginSize && position.y < window.getSize().y - marginSize) {
            window.draw(adjustedBubble);
            window.draw(adjustedText);
        }
    }
    window.draw(lowerBackground);
    window.draw(lowerBar);
    window.draw(upperBar);
    window.draw(inputBox);
    window.draw(inputText);

    sendButton.render(window);
    wizzButton.render(window);
}

Button& UIManager::getSendButton() {
    return sendButton;
}

Button& UIManager::getWizzButton() {
    return wizzButton;
}
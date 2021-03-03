#include "Notifier.hpp"

int main() {
  Notifier          notifier;
  DiscordDecorator  discordNotifier{&notifier};
  SlackDecorator    slackNotifier{&discordNotifier};

  slackNotifier.notify();
  
  return 0;
}
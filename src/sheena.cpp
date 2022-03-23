/// This example demonstrates a minimal bot that just echoes back what it reads.

#include <libtelegram/libtelegram.h>

auto main() -> int
{
  // Read the token.secret
  std::ifstream infile("/etc/tbsheena/token.secret");

  if (!infile.good())
  {
    std::cerr << "Please provide token.secret" << std::endl;
    return EXIT_FAILURE;
  }

  std::string token;
  std::getline(infile, token);

  // create a sender with our token for outgoing messages
  telegram::sender sender(token);

  // create a polling listener which will process incoming requests, polling using the sender
  telegram::listener::poll listener(sender);

  // we set a callback for receiving messages in native format, using a lambda for convenience
  listener.set_callback_message([&](telegram::types::message const &message)
                                {
                                  std::string messagetext(*message.text);
                                  if (std::string::npos != messagetext.find("Musik"))
                                  {
                                    std::string const reply("Ich steh total auf Punk.");

                                    // send our reply from within the callback
                                    sender.send_message(message.chat.id, reply);
                                  } });

  listener.run(); // launch the listener - this call blocks until the listener is terminated
  return EXIT_SUCCESS;
};

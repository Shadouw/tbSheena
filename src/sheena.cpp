#include <unistd.h>

#include <algorithm>
#include <map>
#include <vector>
#include <string>

#include <libtelegram/libtelegram.h>

using namespace std;

void printhelp(int argc, char **argv)
{
  cout << "Call " << argv[0] << endl;
  cout << " -t [Token]: This is mandatory" << endl;
  cout << " -c [Configuration Folder]: Default is /etc/tbsheena/" << endl;
}

auto main(int argc, char **argv) -> int
{
  std::string token;
  std::string conffolder("/etc/tbsheena/");
  std::srand(std::time(nullptr)); // use current time as seed for random generator

  int c = 0;
  while ((c = getopt(argc, argv, "t:c:")) != -1)
  {
    switch (c)
    {
    case 't':
      token = optarg;
      break;
    case 'c':
      conffolder = optarg;
      break;
    }
  }

  if ("" == token)
  {
    printhelp(argc, argv);
    return EXIT_FAILURE;
  }

  if ( '/' != conffolder.back() )
  {
    conffolder += '/';
  }

  cout << "Using configuration in folder: " << conffolder << endl;

  map<string,vector<string>> phrases;

  // Read phrases.txt
  {
    std::ifstream infile(conffolder + "phrases.txt");

    if (!infile.good())
    {
      std::cerr << "Cannot find file " << conffolder << "phrases.txt" << std::endl;
      return EXIT_FAILURE;
    }

    for ( std::string line; getline(infile, line); )
    {
      // Find :
      size_t pos = line.find(":");
      if ( std::string::npos != pos )
      {
        string keyword (line.substr(0,pos));
        string const answer  (line.substr(pos+1));

        std::transform(keyword.begin(), keyword.end(), keyword.begin(),
          [](unsigned char c){ return std::tolower(c); });

        phrases[keyword].push_back(answer);
      }
    }
  }
  // create a sender with our token for outgoing messages
  telegram::sender sender(token);

  // create a polling listener which will process incoming requests, polling using the sender
  telegram::listener::poll listener(sender);

  listener.set_callback_message_json([&](nlohmann::json const &input)
  {
    std::string const message_text(input.at("text").get<std::string>());
    std::string const message_sender(input["from"]["first_name"].get<std::string>());
    int_fast64_t const message_chat_id(input["chat"]["id"]);

    std::string message_text_lower(message_text);
    std::transform(message_text_lower.begin(), message_text_lower.end(), message_text_lower.begin(),
          [](unsigned char c){ return std::tolower(c); });

    std::string reply;

    for ( auto phrasevector : phrases )
    {
      if (std::string::npos != message_text_lower.find(phrasevector.first))
      {
        std::size_t const r = std::rand()/((RAND_MAX + 1u)/phrasevector.second.size());
        reply += phrasevector.second.at(r) + " ";
      }
    }

    sender.send_message(message_chat_id, reply);
  });

  //sender.send_message(message_chat_id, message_sender + " sent \"" + message_text + "\" to chat id " + std::to_string(message_chat_id)); // send our reply from within the callback }); });

  listener.run(); // launch the listener - this call blocks until the listener is terminated
  return EXIT_SUCCESS;
};

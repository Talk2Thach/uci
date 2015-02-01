#include <iostream>
#include <string>

int main()
{
  std::string first_name, last_name, email;
  std::cout << "Please input your first name: " << std::endl;
  std::cin >> first_name;
  std::cout << "Please input your last name: " << std::endl;
  std::cin >> last_name;
  std::cout << "Please input your email name: " << std::endl;
  std::cin >> email;

  std::cout << "From: Customer Service <customer_service@ics45c.com>" << std::endl
            << "To: " << first_name << " " << last_name << " <" << email << ">" << std::endl
            << "Subject: ICS45C appreciates your business!" << std::endl
            << std::endl
            << "Dear " << first_name << " " << last_name << ":" << std::endl
            << std::endl
            << "We are writing today to thank you for your business, and to invite you" << std::endl
            << "to contact us if you have any comments and concerns about your recent" << std::endl
            << "order.  If so, please email us at customer_service@ics45c.com and we" << std::endl
            << "would be delighted to discuss them with you." << std::endl
            << std::endl
            << std::endl
            << "Many Thanks," << std::endl
            << std::endl
            << "ICS45C Customer Service Team" << std::endl;
  return 0;
}


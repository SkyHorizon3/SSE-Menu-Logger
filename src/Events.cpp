#include "Events.h"

RE::BSEventNotifyControl Event::ProcessEvent(const RE::MenuOpenCloseEvent* a_event, RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_source)
{
	if (!a_event || !a_source)
		return RE::BSEventNotifyControl::kContinue;

	const auto& menuName = a_event->menuName;
	const auto& opening = a_event->opening;

	if (!opening)
		return RE::BSEventNotifyControl::kContinue;

	const auto menu = RE::UI::GetSingleton()->GetMenu(menuName).get();
	if (!menu)
	{
		log(std::format("Couldn't get {}!", menuName.c_str()));
		return RE::BSEventNotifyControl::kContinue;
	}

	const auto& movie = menu->uiMovie.get();
	if (!movie)
	{
		log(std::format("Couldn't get {} movie!", menuName.c_str()));
		return RE::BSEventNotifyControl::kContinue;
	}

	const auto def = movie->GetMovieDef();
	if (!def)
	{
		log(std::format("Couldn't get {} movie def!", menuName.c_str()));
		return RE::BSEventNotifyControl::kContinue;
	}

	const std::string message = std::format("Open menu: {} - Filepath: {}", menuName.c_str(), def->GetFileURL());

	log(message);

	return RE::BSEventNotifyControl::kContinue;
}

void Event::log(const std::string& message)
{
	SKSE::log::info("{}", message);
	RE::ConsoleLog::GetSingleton()->Print(message.c_str());
}
/* FSM code for use in Presentation */

void drive(MovableEntity* entity) {
    if (typeid(*entity) == typeid(Car)) {
        Car* car = dynamic_cast<Car*>(entity);
        float carDelta;
        sf::Clock carClock;

        car->setState(Car::State::DRIVING);
        while(car->isRunning()) {
            ts::restartDelta(carDelta, carClock);
            Car::State state = car->getState();
            switch(state) {
                case Car::State::DRIVING: { // need to define a scope to declare variables
                    Test::orbit(*car, carDelta, boundaries);
                    break;
                }
                case Car::State::ARRIVED:
                    car->setDestinationVertex(car->getNextDestination());
                    car->setNextDestination(NULL);
                    car->setState(Car::State::DRIVING);
                    break;
                case Car::State::PARKING:
                    Test::exitOrbit(*car, carDelta);
                    break;
                case Car::State::PARKED:
                    removeCar(car);
                    break;
            }
        }
   }
}

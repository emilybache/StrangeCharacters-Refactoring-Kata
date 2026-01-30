from character import Character


class CharacterFactory:
    @staticmethod
    def strange_characters():
        joyce = Character("Joyce", "Byers", isMonster=False)
        jim = Character("Jim", "Hopper", isMonster=False)
        mike = Character("Mike", "Wheeler", isMonster=False)
        eleven = Character("Eleven", isMonster=False)
        dustin = Character("Dustin", "Henderson", isMonster=False)
        lucas = Character("Lucas", "Sinclair", isMonster=False)
        nancy = Character("Nancy", "Wheeler", isMonster=False)
        jonathan = Character("Jonathan", "Byers", isMonster=False)
        will = Character("Will", "Byers", isMonster=False)
        karen = Character("Karen", "Wheeler", isMonster=False)
        holly = Character("Holly", "Wheeler", isMonster=False)
        steve = Character("Steve", "Harrington", isMonster=False)
        mindflayer = Character("Mindflayer", isMonster=True)
        demagorgon = Character("Demagorgon", isMonster=True)
        demadog = Character("Demadog", isMonster=True)
        mrwhatsit = Character("MrWhatsit", isMonster=True)

        joyce._add_child(jonathan)
        joyce._add_child(will)
        jim._add_child(eleven)
        karen._add_child(nancy)
        karen._add_child(mike)
        karen._add_child(holly)

        eleven._nemesis = demagorgon
        will._nemesis = mindflayer
        dustin._nemesis = demadog
        holly._nemesis = mrwhatsit

        return [
            joyce,
            jim,
            mike,
            will,
            eleven,
            dustin,
            lucas,
            nancy,
            jonathan,
            mindflayer,
            demagorgon,
            demadog,
            karen,
            holly,
            mrwhatsit,
            steve,
        ]

    @staticmethod
    def wheeler_family():
        mike = Character("Mike", "Wheeler", isMonster=False)
        nancy = Character("Nancy", "Wheeler", isMonster=False)
        karen = Character("Karen", "Wheeler", isMonster=False)
        holly = Character("Holly", "Wheeler", isMonster=False)

        karen._add_child(nancy)
        karen._add_child(mike)
        karen._add_child(holly)

        return [
            nancy,
            karen,
            mike,
            holly,
        ]

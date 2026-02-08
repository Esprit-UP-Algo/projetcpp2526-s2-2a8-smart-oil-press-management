# Guide d'Intégration - Gestion Client + Stock

## 📋 Ce que j'ai créé pour vous

J'ai créé une structure de projet intégrée qui utilise un **StackedWidget** pour naviguer entre la gestion Client et la gestion Stock.

## 📁 Structure des fichiers

```
projet_integre/
├── main.cpp                 # Point d'entrée de l'application
├── mainwindow.h            # Header du MainWindow avec StackedWidget
├── mainwindow.cpp          # Implémentation de la navigation
├── mainwindow.ui           # Interface avec sidebar + StackedWidget
├── clientwidget.h          # Header de la page Client
├── clientwidget.cpp        # Implémentation page Client
├── clientwidget.ui         # Interface gestion Client (À CRÉER)
├── stockwidget.h           # Header de la page Stock
├── stockwidget.cpp         # Implémentation page Stock
├── stockwidget.ui          # Interface gestion Stock (À CRÉER)
├── projet.pro              # Fichier de projet Qt
├── resources.qrc           # Fichier de ressources
└── images/
    └── logo.png            # Votre logo
```

## 🔧 Étapes pour finaliser l'intégration

### Étape 1 : Créer clientwidget.ui

1. Ouvrez Qt Designer
2. Créez un nouveau fichier **Widget** (pas MainWindow !)
3. Copiez TOUT le contenu de votre interface Client (le TabWidget avec tableau et formulaire)
4. **IMPORTANT** : Ne copiez PAS :
   - La sidebar (à gauche)
   - Le header en haut
   - Copiez SEULEMENT le QTabWidget et son contenu
5. Sauvegardez comme `clientwidget.ui`

### Étape 2 : Créer stockwidget.ui

1. Même chose pour la gestion Stock
2. Copiez SEULEMENT le contenu central (sans sidebar ni header)
3. Sauvegardez comme `stockwidget.ui`

### Étape 3 : Copier les fichiers dans votre projet

1. Créez un nouveau dossier `projet_integre`
2. Copiez TOUS les fichiers que je vous ai donnés
3. Ajoutez vos fichiers `.ui` créés aux étapes 1 et 2
4. Copiez le dossier `images/` avec votre logo

### Étape 4 : Compiler et tester

1. Ouvrez `projet.pro` dans Qt Creator
2. Build → Rebuild All
3. Lancez l'application

## ✨ Comment ça fonctionne

- **Bouton "👤 Clients"** → Affiche la page de gestion Client
- **Bouton "📦 Stock"** → Affiche la page de gestion Stock
- Le titre du header change automatiquement
- Les autres boutons sont prêts pour de futures intégrations

## 🎯 Ce qui reste à faire

1. Créer les fichiers `.ui` pour Client et Stock (voir Étapes 1 et 2)
2. Si vous avez du code de connexion à la base de données :
   - Ajoutez-le dans `clientwidget.cpp` pour la page Client
   - Ajoutez-le dans `stockwidget.cpp` pour la page Stock
3. Connecter les boutons (Ajouter, Modifier, Supprimer) dans chaque widget

## ❓ Besoin d'aide ?

Si vous avez des difficultés, envoyez-moi :
- Le fichier .ui complet de votre interface Client actuelle
- Le fichier .ui complet de votre interface Stock
Je les convertirai en `clientwidget.ui` et `stockwidget.ui` pour vous !

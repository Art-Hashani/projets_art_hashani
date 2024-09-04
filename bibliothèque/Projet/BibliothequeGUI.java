import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;

public class BibliothequeGUI extends JFrame {
    private ArrayList<Document> documents;
    private ArrayList<OrdinateurPortable> ordinateurs;
    private JButton booksButton;
    private JButton computersButton;
    private JButton loginButton;
    private JButton registerButton;
    private JPanel buttonsPanel;
    private JPanel booksPanel;

    private boolean loggedIn;
    private String username;

    public BibliothequeGUI() {
        setTitle("Gestion de Bibliothèque");
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setSize(400, 400);

        documents = new ArrayList<>();
        ordinateurs = new ArrayList<>();

        // Ajout de livres
        documents.add(new Livre("Harry Potter", "J.K. Rowling", "Bloomsbury"));
        documents.add(new Livre("Le Seigneur des Anneaux", "J.R.R. Tolkien", "Christian Bourgois"));
        documents.add(new Livre("1984", "George Orwell", "Secker & Warburg"));
        documents.add(new Livre("Fondation", "Isaac Asimov", "Doubleday"));
        documents.add(new Livre("Le Petit Prince", "Antoine de Saint-Exupéry", "Reynal & Hitchcock"));
        documents.add(new Livre("Guerre et Paix", "Léon Tolstoï", "L'Édition française illustrée"));
        documents.add(new Livre("Orgueil et Préjugés", "Jane Austen", "T. Egerton, Whitehall"));
        documents.add(new Livre("Les Misérables", "Victor Hugo", "A. Lacroix, Verboeckhoven & Cie"));
        documents.add(new Livre("Crime et Châtiment", "Fiodor Dostoïevski", "Éditions Werdet et Lequien fils"));

        // Ajout d'ordinateurs portables
        ordinateurs.add(new OrdinateurPortable(false, "Apple", Os.LINUX));
        ordinateurs.add(new OrdinateurPortable(false, "Dell", Os.WINDOWS));
        ordinateurs.add(new OrdinateurPortable(false, "Lenovo", Os.WINDOWS));
        ordinateurs.add(new OrdinateurPortable(false, "HP", Os.LINUX));
        ordinateurs.add(new OrdinateurPortable(false, "Asus", Os.WINDOWS));

        loggedIn = false;
        username = "";

        showLoginOrRegisterDialog(); // Afficher la boîte de dialogue de connexion ou de création de compte au démarrage
    }

    private void createButtonsPanel() {
        buttonsPanel = new JPanel();
        booksButton = new JButton("Livres");
        computersButton = new JButton("Ordinateurs Portables");

        booksButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                displayDocumentsOfType(Livre.class);
            }
        });

        computersButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                displayComputers();
            }
        });

        buttonsPanel.add(booksButton);
        buttonsPanel.add(computersButton);

        add(buttonsPanel, BorderLayout.NORTH);

        setVisible(true);
    }

    private void displayDocumentsOfType(Class<? extends Document> type) {
        if (booksPanel != null) {
            remove(booksPanel);
        }
        booksPanel = new JPanel();
        booksPanel.setLayout(new GridLayout(0, 1));
    
        System.out.println("Nombre de documents dans la liste : " + documents.size());
    
        for (Document document : documents) {
            System.out.println("Type de document : " + document.getClass());
            if (type.isInstance(document)) {
                JButton button = new JButton(document.getTitre());
                button.addActionListener(new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent e) {
                        int choice = JOptionPane.showOptionDialog(BibliothequeGUI.this, "Que voulez-vous faire avec ce document?",
                                "Choix d'action", JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE,
                                null, new String[]{"Emprunter", "Rendre"}, "Emprunter");
                        if (choice == JOptionPane.YES_OPTION) {
                            // Logique pour emprunter le document
                            JOptionPane.showMessageDialog(BibliothequeGUI.this, "Document emprunté avec succès !");
                        } else if (choice == JOptionPane.NO_OPTION) {
                            // Logique pour rendre le document
                            JOptionPane.showMessageDialog(BibliothequeGUI.this, "Document rendu avec succès !");
                        }
                    }
                });
                booksPanel.add(button);
            }
        }
        add(booksPanel, BorderLayout.CENTER);
        revalidate();
        repaint();
    }
    
    

    private void displayComputers() {
        if (booksPanel != null) {
            remove(booksPanel);
        }
        booksPanel = new JPanel();
        booksPanel.setLayout(new GridLayout(0, 1));

        for (OrdinateurPortable computer : ordinateurs) {
            JButton button = new JButton(computer.getMarque());
            button.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    int choice = JOptionPane.showOptionDialog(BibliothequeGUI.this, "Que voulez-vous faire avec cet ordinateur portable?",
                            "Choix d'action", JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE,
                            null, new String[]{"Emprunter", "Rendre"}, "Emprunter");
                    if (choice == JOptionPane.YES_OPTION) {
                        // Logique pour emprunter l'ordinateur portable
                        JOptionPane.showMessageDialog(BibliothequeGUI.this, "Ordinateur portable emprunté avec succès !");
                    } else if (choice == JOptionPane.NO_OPTION) {
                        // Logique pour rendre l'ordinateur portable
                        JOptionPane.showMessageDialog(BibliothequeGUI.this, "Ordinateur portable rendu avec succès !");
                    }
                }
            });
            booksPanel.add(button);
        }
        add(booksPanel, BorderLayout.CENTER);
        revalidate();
        repaint();
    }

    private void showLoginOrRegisterDialog() {
        Object[] options = {"Se Connecter", "Créer un Compte", "Quitter"};
        int choice = JOptionPane.showOptionDialog(this,
                "Voulez-vous vous connecter ou créer un compte?",
                "Connexion/Inscription",
                JOptionPane.YES_NO_CANCEL_OPTION,
                JOptionPane.QUESTION_MESSAGE,
                null,
                options,
                options[2]);

        switch (choice) {
            case JOptionPane.YES_OPTION: // Se Connecter
                showLoginDialog();
                break;
            case JOptionPane.NO_OPTION: // Créer un Compte
                showRegisterDialog();
                break;
            case JOptionPane.CANCEL_OPTION: // Quitter
            case JOptionPane.CLOSED_OPTION:
                System.exit(0);
                break;
        }
    }

    private void showLoginDialog() {
        JTextField usernameField = new JTextField();
        JPasswordField passwordField = new JPasswordField();
        Object[] message = {
                "Nom d'utilisateur:", usernameField,
                "Mot de passe:", passwordField
        };

        int option = JOptionPane.showConfirmDialog(this, message, "Connexion", JOptionPane.OK_CANCEL_OPTION);
        if (option == JOptionPane.OK_OPTION) {
            String username = usernameField.getText();
            char[] password = passwordField.getPassword();
            // Vérifiez l'authentification
            if (authenticate(username, password)) {
                loggedIn = true;
                this.username = username;
                createButtonsPanel(); // Créer les boutons pour afficher les livres et les ordinateurs portables après la connexion
            } else {
                JOptionPane.showMessageDialog(this, "Nom d'utilisateur ou mot de passe incorrect !");
                showLoginOrRegisterDialog(); // Affiche à nouveau la boîte de dialogue de connexion ou de création de compte
            }
        } else {
            showLoginOrRegisterDialog(); // Affiche à nouveau la boîte de dialogue de connexion ou de création de compte
        }
    }

    private void showRegisterDialog() {
        JTextField usernameField = new JTextField();
        JPasswordField passwordField = new JPasswordField();
        JTextField emailField = new JTextField();
        // Ajoutez d'autres champs pour les informations supplémentaires requises

        Object[] message = {
                "Nom d'utilisateur:", usernameField,
                "Mot de passe:", passwordField,
                "Email:", emailField
                // Ajoutez d'autres champs pour les informations supplémentaires requises
        };

        int option = JOptionPane.showConfirmDialog(this, message, "Créer un Compte", JOptionPane.OK_CANCEL_OPTION);
        if (option == JOptionPane.OK_OPTION) {
            String username = usernameField.getText();
            char[] password = passwordField.getPassword();
            String email = emailField.getText();
            // Récupérez les autres informations requises
            // Enregistrez les informations dans votre système (base de données, etc.)
            // Puis affichez la boîte de dialogue de connexion
            JOptionPane.showMessageDialog(this, "Compte créé avec succès !");
            showLoginDialog(); // Afficher la boîte de dialogue de connexion après la création du compte
        } else {
            showLoginOrRegisterDialog(); // Affiche à nouveau la boîte de dialogue de connexion ou de création de compte
        }
    }

    private boolean authenticate(String username, char[] password) {
        // Logique pour l'authentification (vérification dans une base de données, etc.)
        // Pour simplifier, nous supposons que l'authentification est toujours réussie
        return true;
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                new BibliothequeGUI();
            }
        });
    }
}
